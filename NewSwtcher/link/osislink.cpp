#include <QMutexLocker>
#include "link/osislink.h"

OsisLink::OsisLink(const QString &connectionGroupName, Configuration& configFile, DataQueue* dataQueue, QObject *parent)
   : BaseLink(connectionGroupName, configFile, parent)
   , qtcp_Socket(0)
   , osisDataQueue(dataQueue)
   , socketReconnectNeeded(false)
{
}

void OsisLink::SocketConnectRequest()
{
   if (qtcp_Socket)
   {
      SocketDisconnectRequest();
   }

   QMutexLocker lock(&M);

   RemainingQBA.clear();

   qtcp_Socket = new QTcpSocket(this);
   connect(qtcp_Socket, SIGNAL(connected()), this, SLOT(SlotSocketConnected()));
   connect(qtcp_Socket, SIGNAL(disconnected()), this, SLOT(SlotSocketDisconnected()));
   connect(qtcp_Socket, SIGNAL(readyRead()), this, SLOT(SlotSocketReadyRead()));
   connect(qtcp_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotSocketError(QAbstractSocket::SocketError)));

   Reconnect();
}

void OsisLink::SocketDisconnectRequest()
{
   QMutexLocker lock(&M);

   if (qtcp_Socket)
   {
      qtcp_Socket->disconnect();
      disconnect(qtcp_Socket, 0, 0, 0);
      if (qtcp_Socket && qtcp_Socket->state() == QAbstractSocket::ConnectedState)
      {
         qtcp_Socket->disconnectFromHost();
         qtcp_Socket->close();
      }
      delete qtcp_Socket;
      qtcp_Socket = 0;

      SlotSocketDisconnected();
   }
}

void OsisLink::SocketConnected()
{
   socketReconnectNeeded = false;
}

void OsisLink::SocketDisconnected()
{
   if (socketReconnectNeeded)
   {
      socketReconnectNeeded = false;
      Reconnect();
   }
}

void OsisLink::SlotSocketReadyRead()
{
   QMutexLocker lock(&M);

   if (qtcp_Socket && qtcp_Socket->state() == QAbstractSocket::ConnectedState)
   {
       ProcessData(qtcp_Socket->readAll());
   }
}

void OsisLink::SlotSocketError(QAbstractSocket::SocketError error)
{
   qInfo() << GetGroupName() + " Socket error: " << error;

   if (error == QAbstractSocket::RemoteHostClosedError)
   {
      socketReconnectNeeded = true;
   }
   else
   {
      Reconnect();
   }
}

void OsisLink::Reconnect()
{
   GetIpInfo(Host, Port);
   qtcp_Socket->connectToHost(Host, Port.toShort(), QIODevice::ReadOnly);
}

const quint8 STX = 0x02;
const quint8 ETX = 0x03;

void OsisLink::ProcessData(QByteArray qba)
{
   qInfo() << qba.constData();
   // Frame1: s........es....es...
   // Frame2: ....................
   // Frame3: es
   // Frame4: ...es
   // Frame5: ...e
   int pos_STX = -1;
   int pos_ETX = -1;
   while (!qba.isEmpty())
   {
      pos_STX = qba.indexOf(STX);
      pos_ETX = qba.indexOf(ETX);

      if (RemainingQBA.isEmpty())
      {
         if (pos_STX < 0)
         {  // .....e // ......
            qba.clear();
            return;
         }
         else
         {
            if (pos_STX != 0)
            {  // ...s...e
               qba.remove(0, pos_STX);
               continue;
            }
            if (pos_ETX != -1)
            {
               if (pos_STX < pos_ETX)
               {  // s...es....
                  QByteArray* Data = new QByteArray(qba.mid(1, pos_ETX - 1));
                  osisDataQueue->AddData(Data);
                  qba.remove(0, pos_ETX + 1);
                  continue;
               }
            }
            else
            {  // s.....
               RemainingQBA.append(qba.mid(1));
               qba.clear();
               return;
            }
         }
      }
      else
      {
         if (pos_ETX < 0)
         {
            if (pos_STX != -1)
            {  // ......s....
               RemainingQBA.clear();
               qba.remove(0, pos_STX);
               continue;
            }
            else
            {   // .........
                RemainingQBA.append(qba);
                qba.clear();
                return;
            }
         }
         else
         {
            if (pos_STX == -1)
            { // .....e
               QByteArray* Data = new QByteArray(RemainingQBA.append(qba.mid(0, pos_ETX - 1)));
               osisDataQueue->AddData(Data);
               RemainingQBA.clear();
               qba.clear();
               return;
            }
            else
            {
               if (pos_ETX < pos_STX)
               {  // ...es....
                  QByteArray* Data = new QByteArray(RemainingQBA.append(qba.mid(0, pos_ETX - 1)));
                  osisDataQueue->AddData(Data);
                  qba.remove(0, pos_ETX + 1);
                  RemainingQBA.clear();
                  continue;
               }
               else
               {  // s....e , .....s....e
                  RemainingQBA.clear();
                  qba.remove(0, pos_STX);
                  continue;
               }
            }
         }
      }
   }
}
