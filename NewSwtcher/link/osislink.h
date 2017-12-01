#ifndef OSISLINK_H
#define OSISLINK_H

#include <QTcpSocket>
#include <QMutex>
#include <QByteArray>
#include <configuration.h>
#include <osis/dataqueue.h>
#include "link/linkbase.h"

class OsisLink : public BaseLink
{
   Q_OBJECT
public:
   explicit OsisLink(const QString& connectionGroupName, Configuration& configFile, DataQueue* dataQueue, QObject *parent = nullptr);

signals:

public slots:
   void SlotSocketReadyRead();
   void SlotSocketError(QAbstractSocket::SocketError error);

private:
   virtual void SocketConnectRequest();
   virtual void SocketDisconnectRequest();
   virtual void SocketConnected();
   virtual void SocketDisconnected();

   virtual void ThreadStarted();

   void ProcessData(QByteArray qba);
   void Reconnect();

private:
   QThread osisLinkThread;
   QTcpSocket* qtcp_Socket;
   QMutex M;
   DataQueue* osisDataQueue;
   QByteArray RemainingQBA;
   QString Host;
   QString Port;
   bool socketReconnectNeeded;
};

#endif // OSISLINK_H
