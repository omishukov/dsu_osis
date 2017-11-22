#ifndef OSISLINK_H
#define OSISLINK_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMutex>
#include <QByteArray>
#include <link/linkif.h>
#include <ui/uilinkif.h>
#include <configuration.h>
#include <osis/dataqueue.h>

class BaseLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit BaseLink(const QString& connectionGroupName, Configuration& configFile, DataQueue* dataQueue, QObject *parent = nullptr);

   void Connect();
   void Disconnect();

   void Start();
   void Stop();

   void SetUiIf(UiLinkIf* uiIf) { ui_If = uiIf; }

signals:
   void linkConnect();
   void linkDisconnect();
   void terminate();

public slots:
   void SlotThreadStarted();
   void SlotThreadFinished();

   void SlotSocketConnected();
   void SlotSocketDisconnected();

   void socketConnected();
   void socketDisconnected();
   void socketReadyRead();
   void socketError(QAbstractSocket::SocketError error);

   void SlotThreadTerminateRequest();

private:
   void ProcessData(QByteArray qba);
   void Reconnect();

private:
   QThread osisLinkThread;
   QTcpSocket* qtcp_Socket;
   UiLinkIf* ui_If;
   QMutex M;
   DataQueue* osisDataQueue;
   QByteArray RemainingQBA;
   QString Host;
   QString Port;
   bool socketServerClosed;
};

#endif // OSISLINK_H
