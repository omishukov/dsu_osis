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

class OsisLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit OsisLink(const QString& connectionGroupName, Configuration& configFile, DataQueue* dataQueue, QObject *parent = nullptr);

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
   void threadStarted();
   void threadFinished();

   void socketConnect();
   void socketDisconnect();

   void socketConnected();
   void socketDisconnected();
   void socketReadyRead();
   void socketError(QAbstractSocket::SocketError error);

   void threadTerminate();

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
   bool terminateRequest;
   bool socketServerClosed;
};

#endif // OSISLINK_H
