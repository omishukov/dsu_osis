#include "isucalclink.h"

IsuCalcLinkThread::IsuCalcLinkThread(QObject* parent)
   : QObject(parent)
   , Port(0)
   , Reconnect(false)
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

}

void IsuCalcLinkThread::Disconnected()
{
   if (Reconnect)
   {

   }
}

void IsuCalcLinkThread::ReadyRead()
{

}

void IsuCalcLinkThread::SocketError()
{

}
