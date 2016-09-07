#include "isucalclink.h"

IsuCalcLinkThread::IsuCalcLinkThread(QObject* parent)
   : QObject(parent)
   , Port(0)
   , Reconnect(false)
   , Timer(0)
{

}

void IsuCalcLinkThread::ChangedSettings(const QString& hostName, quint16 port, uint reconnect)
{
   HostName = hostName;
   Port = port;
   Reconnect = reconnect?true:false;
}

void IsuCalcLinkThread::Initialize()
{
   connect(&Socket, SIGNAL(connected()),this, SLOT(Connected()));
   connect(&Socket, SIGNAL(disconnected()),this, SLOT(Disconnected()));
   connect(&Socket, SIGNAL(readyRead()),this, SLOT(ReadyRead()));
   connect(&Socket, SIGNAL(error()),this, SLOT(SocketError()));
   Timer = new QTimer();
   Timer->setSingleShot(true);
   connect(Timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
}

void IsuCalcLinkThread::Uninit()
{
   if (Socket.state() != QAbstractSocket::UnconnectedState)
   {
      Socket.reset();
      Socket.close();
   }
}

void IsuCalcLinkThread::Connected()
{
   emit Established();
}

void IsuCalcLinkThread::Disconnected()
{
}

void IsuCalcLinkThread::ReadyRead()
{

}

void IsuCalcLinkThread::SocketError()
{
   Disconnected();
}

void IsuCalcLinkThread::Establish()
{
   QTcpSocket::SocketState connState = Socket.state();
   if (connState == QAbstractSocket::UnconnectedState)
   {
      Timer->start(2250);
      Socket.connectToHost(HostName, Port, QIODevice::ReadOnly);
   }
}

void IsuCalcLinkThread::TimerExpired()
{
   QTcpSocket::SocketState connState = Socket.state();

   if (Reconnect && connState == QAbstractSocket::UnconnectedState)
   {
      Establish();
   }
   else
   {
       if (Socket.state() == QAbstractSocket::UnconnectedState)
       {
           Disconnected();
       }
   }
}
