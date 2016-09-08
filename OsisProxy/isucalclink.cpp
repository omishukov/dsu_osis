#include "isucalclink.h"

IsuCalcLinkThread::IsuCalcLinkThread(QObject* parent)
   : QObject(parent)
   , Port(0)
   , Reconnect(false)
   , Socket(0)
   , Timer(0)
   , IgnoreReconnect(false)
{

}

IsuCalcLinkThread::~IsuCalcLinkThread()
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
   Socket = new QTcpSocket;
   connect(Socket, SIGNAL(connected()), this, SLOT(Connected()));
   connect(Socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
   connect(Socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
   connect(Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
   Timer = new QTimer;
   Timer->setSingleShot(true);
   connect(Timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
}

void IsuCalcLinkThread::Uninit()
{
   StopConnection();
   delete Timer;
   Timer = 0;
   delete Socket;
   Socket = 0;
}

void IsuCalcLinkThread::Connected()
{
   emit Established();
}

void IsuCalcLinkThread::Disconnected()
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

void IsuCalcLinkThread::ReadyRead()
{

}

void IsuCalcLinkThread::SocketError(QAbstractSocket::SocketError err)
{
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::UnconnectedState && Reconnect)
   {
      Timer->start(2250);
   }
   else if (connState != QAbstractSocket::ConnectedState)
   {
      emit IsuCalcDisconnected();
   }
}

void IsuCalcLinkThread::Establish()
{
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::UnconnectedState)
   {
      emit Reconnecting();
      Socket->connectToHost(HostName, Port, QIODevice::ReadOnly);
   }
}

void IsuCalcLinkThread::StopConnection()
{
   Timer->stop();
   if (Socket->state() != QAbstractSocket::UnconnectedState)
   {
      IgnoreReconnect = true;
      Socket->disconnectFromHost();
      Socket->close();
   }
   else
   {
      emit IsuCalcDisconnected();
   }
}

void IsuCalcLinkThread::TimerExpired()
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
