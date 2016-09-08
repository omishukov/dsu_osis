#include "isucalclink.h"

IsuCalcLink::IsuCalcLink(QObject* parent)
   : QObject(parent)
   , Port(0)
   , Reconnect(false)
   , Socket(0)
   , Timer(0)
   , IgnoreReconnect(false)
   , DataIf(0)
{

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
   Socket = new QTcpSocket;
   connect(Socket, SIGNAL(connected()), this, SLOT(Connected()));
   connect(Socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
   connect(Socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
   connect(Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
   Timer = new QTimer;
   Timer->setSingleShot(true);
   connect(Timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
}

void IsuCalcLink::Uninit()
{
   StopConnection();
   delete Timer;
   Timer = 0;
   delete Socket;
   Socket = 0;
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
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::ConnectedState)
   {
      QByteArray* qba = new QByteArray(Socket->readAll());
      DataIf->AddData(qba);
   }
}

void IsuCalcLink::SocketError(QAbstractSocket::SocketError err)
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

void IsuCalcLink::Establish()
{
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::UnconnectedState)
   {
      emit Reconnecting();
      Socket->connectToHost(HostName, Port, QIODevice::ReadOnly);
   }
}

void IsuCalcLink::StopConnection()
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
