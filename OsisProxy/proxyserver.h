#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QMultiMap>

class ProxyServer : public QObject
{
   Q_OBJECT
public:
   explicit ProxyServer(QObject *parent = 0);
   ~ProxyServer();

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

private:
   void SendCachedOsisData(QTcpSocket* socket);

   QTcpServer* Server;
   quint16 Port;
   bool Initialized;
   QMultiMap<quint32, QTcpSocket*> Clients;
};

#endif // PROXYSERVER_H
