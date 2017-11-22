#ifndef OBSLINK_H
#define OBSLINK_H

#include <QWebSocket>
#include <link/linkif.h>
#include <configuration.h>
#include "link/linkbase.h"

class ObsLink : public BaseLink
{
   Q_OBJECT
public:
   explicit ObsLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

signals:

public slots:
   void SlotSocketReadyRead();
   void SlotSocketError(QAbstractSocket::SocketError error);

private:
   virtual void SocketConnectRequest();
   virtual void SocketDisconnectRequest();
   virtual void SocketConnected();
   virtual void SocketDisconnected();

private:
   QWebSocket obsWebSocketClient;
   QString Host;
   QString Port;

};

#endif // OBSLINK_H
