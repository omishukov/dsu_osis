#ifndef BASELINK_H
#define BASELINK_H

#include <QObject>
#include <QThread>
#include <link/linkif.h>
#include <ui/uilinkif.h>
#include <configuration.h>

class BaseLink : public QObject, public LinkIf
{
   Q_OBJECT
public:
   explicit BaseLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

   void Connect();
   void Disconnect();

   void Start();
   void Stop();

   void SetUiIf(UiLinkIf* uiIf) { ui_If = uiIf; }

signals:
   void SignalSocketConnectRequest();
   void SignalSocketDisconnectRequest();
   void SignalThreadTerminateRequest();

public slots:
   void SlotThreadStarted();
   void SlotThreadFinished();
   void SlotThreadTerminateRequest();

   void SlotSocketConnectRequest();
   void SlotSocketDisconnectRequest();
   void SlotSocketConnected();
   void SlotSocketDisconnected();

private:
   virtual void ThreadStarted() {}
   virtual void ThreadFinished() {}
   virtual void SocketConnectRequest() = 0;
   virtual void SocketDisconnectRequest() = 0;
   virtual void SocketConnected() = 0;
   virtual void SocketDisconnected() = 0;

private:
   QThread linkThread;
   UiLinkIf* ui_If;

};

#endif // BASELINK_H
