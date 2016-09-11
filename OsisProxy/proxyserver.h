#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QMultiMap>
#include <QMutex>
#include "osisdataproxy.h"

class ProxyServer : public QObject
{
   Q_OBJECT
public:
   explicit ProxyServer(QObject *parent = 0);
   ~ProxyServer();

   void SetProxyIf(OsisDataProxy *proxy) { Proxy = proxy; }

signals:
   void ProxyConnected(quint32);
   void ProxyDisconnected(quint32);

public slots:
   void Initialize();
   void Uninit();
   void ChangedSettings(quint16 port);
   void NewConnection();
   void ClientDisconnected();
   void DisconnectAllClients();
   void DisconnectAllClientsSilent();
   void NewData(QByteArray* qba);

private:
   void SendCachedOsisData(QTcpSocket* socket);

   QTcpServer* Server;
   quint16 Port;
   bool Initialized;
   QMultiMap<quint32, QTcpSocket*> Clients;
   OsisDataProxy *Proxy;
   QMutex M;
};

#endif // PROXYSERVER_H
