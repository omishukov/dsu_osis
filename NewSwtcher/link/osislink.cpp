#include <QMutexLocker>
#include "link/osislink.h"

OsisLink::OsisLink(const QString &connectionGroupName, Configuration& configFile, DataQueue* dataQueue, QObject *parent)
   : QObject(parent)
   , LinkIf(connectionGroupName, configFile)
   , qtcp_Socket(0)
   , ui_If(0)
   , osisDataQueue(dataQueue)
{
   moveToThread(&osisLinkThread);
   connect(&osisLinkThread, SIGNAL(started()), this, SLOT(threadStarted())); // on thread start
   connect(&osisLinkThread, SIGNAL(finished()), this, SLOT(threadFinished())); // on thread stop

   connect(this, SIGNAL(linkConnect()), this, SLOT(socketConnect()), Qt::QueuedConnection);
   connect(this, SIGNAL(linkDisconnect()), this, SLOT(socketDisconnect()), Qt::QueuedConnection);
}

void OsisLink::Connect()
{
   emit linkConnect();
}

void OsisLink::Disconnect()
{
   emit linkDisconnect();
}

void OsisLink::Start()
{
   osisLinkThread.start();
}

void OsisLink::Stop()
{
   socketDisconnect();
   osisLinkThread.quit();
   osisLinkThread.wait();
}

void OsisLink::threadStarted()
{
}

void OsisLink::threadFinished()
{
   socketDisconnect();
}

void OsisLink::socketConnect()
{
   if (qtcp_Socket)
   {
      socketDisconnect();
   }

   QMutexLocker lock(&M);

   RemainingQBA.clear();

   qtcp_Socket = new QTcpSocket(this);
   connect(qtcp_Socket, SIGNAL(connected()), this, SLOT(socketConnected()));
   connect(qtcp_Socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
   connect(qtcp_Socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
   connect(qtcp_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

   GetIpInfo(Host, Port);
   qtcp_Socket->connectToHost(Host, Port.toShort(), QIODevice::ReadOnly);
}

void OsisLink::socketDisconnect()
{
   QMutexLocker lock(&M);

   if (qtcp_Socket)
   {
      disconnect(qtcp_Socket, 0, 0, 0);
      if (qtcp_Socket && qtcp_Socket->isOpen())
      {
         qtcp_Socket->disconnectFromHost();
         qtcp_Socket->close();
         qtcp_Socket->reset();
      }
      delete qtcp_Socket;
      qtcp_Socket = 0;

      socketDisconnected();
   }
}

void OsisLink::socketConnected()
{
   if (!ui_If) { return; }

   ui_If->LinkConnected();
}

void OsisLink::socketDisconnected()
{
   if (!ui_If) { return; }

   ui_If->LinkDisconnected();
}

void OsisLink::socketReadyRead()
{
   QMutexLocker lock(&M);

   if (qtcp_Socket && qtcp_Socket->state() == QAbstractSocket::ConnectedState)
   {
       ProcessData(qtcp_Socket->readAll());
   }
}

void OsisLink::socketError(QAbstractSocket::SocketError error)
{
   qInfo() << "Socket error: " << error << endl;
}

const quint8 STX = 0x02;
const quint8 ETX = 0x03;

void OsisLink::ProcessData(QByteArray qba)
{
   qInfo() << qba.constData() << endl;
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
