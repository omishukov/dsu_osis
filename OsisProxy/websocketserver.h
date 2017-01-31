#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QThread>
#include <QtWebSockets/QWebSocketServer>
#include "dataqueue.h"

class OsisWebsocketServer : public QObject
{
   Q_OBJECT
public:
   explicit OsisWebsocketServer(DataQueue* dataIf, QObject *parent = 0);

signals:

public slots:
   void NewData();
   void Started();
   void Finished();

private:
   DataQueue* DataIf;
   QThread WebsockThread;
   QWebSocketServer Wserver;
};

#endif // WEBSOCKETSERVER_H
