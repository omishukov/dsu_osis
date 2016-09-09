#include <QTcpSocket>
#include "proxyserver.h"

ProxyServer::ProxyServer(QObject *parent)
   : QObject(parent)
   , Port(0)
   , Initialized(false)
{

}

void ProxyServer::Initialize()
{
   Server = new QTcpServer();
   connect(Server, SIGNAL(newConnection()), this, SLOT(NewConnection()));
}

void ProxyServer::ChangedSettings(quint16 port)
{
   if (Port != port)
   {
      Port = port;
      if (Initialized)
      {
         Server->close();
         for (auto client:Clients)
         {
            client->disconnectFromHost();
            delete client;
         }
         Clients.clear();
         emit ProxyDisconnected(0);
      }
      Initialized = Server->listen(QHostAddress::Any, Port);
   }
}

void ProxyServer::NewConnection()
{
   QTcpSocket* newClient = Server->nextPendingConnection();
   if (Clients.isEmpty())
   {
      quint32 addr = newClient->peerAddress().toIPv4Address() & 0xFF;
      emit ProxyConnected(addr);
   }
}
