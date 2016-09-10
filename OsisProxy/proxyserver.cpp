#include <QTcpSocket>
#include "proxyserver.h"

ProxyServer::ProxyServer(QObject *parent)
   : QObject(parent)
   , Port(0)
   , Initialized(false)
{

}

ProxyServer::~ProxyServer()
{
}

void ProxyServer::Initialize()
{
   Server = new QTcpServer();
   connect(Server, SIGNAL(newConnection()), this, SLOT(NewConnection()));
}

void ProxyServer::Uninit()
{
   DisconnectAllClientsSilent();
   Server->close();
   delete Server;
}

void ProxyServer::ChangedSettings(quint16 port)
{
   if (Port != port)
   {
      Port = port;
      if (Initialized)
      {
         Server->close();
         DisconnectAllClients();
         emit ProxyDisconnected(0);
      }
      Initialized = Server->listen(QHostAddress::Any, Port);
   }
}

void ProxyServer::NewConnection()
{
   QTcpSocket* newClient = Server->nextPendingConnection();
   quint32 addr = newClient->peerAddress().toIPv4Address() & 0xFF;
   emit ProxyConnected(addr);
   connect(newClient, SIGNAL(disconnected()), this, SLOT(ClientDisconnected()));
   SendCachedOsisData(newClient);
   Clients.insert(addr, newClient);
}

void ProxyServer::ClientDisconnected()
{
   quint32 addr;
   QTcpSocket* socket = 0;
   QMapIterator<quint32, QTcpSocket*> i(Clients);
   while (i.hasNext())
   {
      i.next();
      socket = i.value();
      addr = i.key();
      if (socket->state() != QAbstractSocket::ConnectedState)
      {
         socket->disconnectFromHost();
         socket->close();
//         delete socket;
         break;
      }
      else
      {
         socket = 0;
      }
   }
   if (socket)
   {
      Clients.remove(addr, socket);
      if (Clients.isEmpty())
      {
         addr = 0;
      }
      emit ProxyDisconnected(addr);
      if (!Clients.isEmpty())
      {
         ClientDisconnected(); // Run again for sure
      }
   }
}

void ProxyServer::DisconnectAllClients()
{
   DisconnectAllClientsSilent();
   emit ProxyDisconnected(0);
}

void ProxyServer::DisconnectAllClientsSilent()
{
   QMapIterator<quint32, QTcpSocket*> i(Clients);
   while (i.hasNext())
   {
      i.next();
      QTcpSocket* socket = i.value();
      {
         socket->disconnectFromHost();
         socket->close();
//         delete socket;
         break;
      }
   }
   Clients.clear();
}

void ProxyServer::SendCachedOsisData(QTcpSocket *socket)
{

}
