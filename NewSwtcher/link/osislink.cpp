#include "link/osislink.h"

OsisLink::OsisLink(const QString &connectionGroupName, Configuration& configFile, QObject *parent)
   : QObject(parent)
   , LinkIf(connectionGroupName, configFile)
   , qtcp_Socket(0)
   , ui_If(0)
{
   moveToThread(&osisLinkThread);
   connect(&osisLinkThread, SIGNAL(started()), this, SLOT(threadStarted())); // on thread start
   connect(&osisLinkThread, SIGNAL(finished()), this, SLOT(threadFinished())); // on thread stop
}

void OsisLink::Connect()
{
   if (qtcp_Socket)
   {
      Disconnect();
   }
   qtcp_Socket = new QTcpSocket();
   connect(qtcp_Socket, SIGNAL(connected()), this, SLOT(socketConnected()));
   connect(qtcp_Socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
   connect(qtcp_Socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
   connect(qtcp_Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

   QString Host;
   QString Port;
   GetIpInfo(Host, Port);
   qtcp_Socket->connectToHost(Host, Port.toShort(), QIODevice::ReadOnly);
}

void OsisLink::Disconnect()
{
   if (qtcp_Socket)
   {
      qtcp_Socket->disconnect();
      qtcp_Socket->disconnectFromHost();
      qtcp_Socket->close();
      qtcp_Socket->reset();
      delete qtcp_Socket;
      qtcp_Socket = 0;
   }
}

void OsisLink::Start()
{
   osisLinkThread.start();
}

void OsisLink::Stop()
{
   Disconnect();
   osisLinkThread.quit();
   osisLinkThread.wait();
}

void OsisLink::threadStarted()
{
}

void OsisLink::threadFinished()
{
}

void OsisLink::socketConnected()
{
   if (ui_If) return;
   ui_If->LinkConnected();
}

void OsisLink::socketDisconnected()
{
   if (ui_If) return;
   ui_If->LinkDisconnected();
}

void OsisLink::socketReadyRead()
{

}

void OsisLink::socketError(QAbstractSocket::SocketError error)
{

}
