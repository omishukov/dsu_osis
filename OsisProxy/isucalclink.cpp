#include <QMutexLocker>
#include "isucalclink.h"

IsuCalcLink::IsuCalcLink(DataQueue* dataIf, QObject* parent)
   : QObject(parent)
   , Port(0)
   , Reconnect(false)
   , Timer(0)
   , IgnoreReconnect(false)
   , DataIf(dataIf)
{
   connect(&m_Socket, SIGNAL(connected()), this, SLOT(Connected()));
   connect(&m_Socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
   connect(&m_Socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
   connect(&m_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
}

IsuCalcLink::~IsuCalcLink()
{
}

void IsuCalcLink::ChangedSettings(const QString& hostName, quint16 port, uint reconnect)
{
   HostName = hostName;
   Port = port;
   Reconnect = reconnect?true:false;
}

void IsuCalcLink::Initialize()
{
   Timer = new QTimer;
   Timer->setSingleShot(true);
   connect(Timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
}

void IsuCalcLink::Uninit()
{
   StopConnection();
   delete Timer;
}

void IsuCalcLink::Connected()
{
   emit Established();
}

void IsuCalcLink::Disconnected()
{
   if (Reconnect && !IgnoreReconnect)
   {
      emit Reconnecting();
      Establish();
   }
   else
   {
      emit IsuCalcDisconnected();
      if (IgnoreReconnect)
      {
         IgnoreReconnect = false;
      }
   }
}

void IsuCalcLink::ReadyRead()
{
   QMutexLocker lock(&m);

   if (m_Socket.state() == QAbstractSocket::ConnectedState)
   {
       ProcessData(m_Socket.readAll());
   }
}

void IsuCalcLink::SocketError(QAbstractSocket::SocketError /*err*/)
{
   QTcpSocket::SocketState connState = m_Socket.state();
   if (connState == QAbstractSocket::UnconnectedState && Reconnect)
   {
      Timer->start(2250);
   }
   else if (connState != QAbstractSocket::ConnectedState)
   {
      emit IsuCalcDisconnected();
   }
}

void IsuCalcLink::Establish()
{
   RemainingQBA.clear();

   if (m_Socket.state() == QAbstractSocket::UnconnectedState)
   {
      emit Reconnecting();
      m_Socket.connectToHost(HostName, Port, QIODevice::ReadOnly);
   }
}

void IsuCalcLink::StopConnection()
{
   Timer->stop();
   if (m_Socket.state() != QAbstractSocket::UnconnectedState)
   {
      IgnoreReconnect = true;
      m_Socket.disconnectFromHost();
      m_Socket.close();
      m_Socket.reset();
   }
   else
   {
      emit IsuCalcDisconnected();
   }
}

void IsuCalcLink::TimerExpired()
{
   if (Reconnect)
   {
      Establish();
   }
   else
   {
      emit IsuCalcDisconnected();
   }
}

const quint8 STX = 0x02;
const quint8 ETX = 0x03;

void IsuCalcLink::ProcessData(QByteArray qba)
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
                  DataIf->AddData(Data);
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
               DataIf->AddData(Data);
               RemainingQBA.clear();
               qba.clear();
               return;
            }
            else
            {
               if (pos_ETX < pos_STX)
               {  // ...es....
                  QByteArray* Data = new QByteArray(RemainingQBA.append(qba.mid(0, pos_ETX - 1)));
                  DataIf->AddData(Data);
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
