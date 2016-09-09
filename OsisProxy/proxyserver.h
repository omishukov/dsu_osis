#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>

class ProxyServer : public QObject
{
   Q_OBJECT
public:
   explicit ProxyServer(QObject *parent = 0);

signals:
   void ProxyConnected(quint32);
   void ProxyDisconnected(quint32);

public slots:
   void Initialize();
   void ChangedSettings(quint16 port);
   void NewConnection();

private:
   QTcpServer* Server;
   quint16 Port;
   bool Initialized;
   QList<QTcpSocket*> Clients;
};

#endif // PROXYSERVER_H
