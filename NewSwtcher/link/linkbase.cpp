#include <QDebug>
#include "link/linkbase.h"

BaseLink::BaseLink(const QString &connectionGroupName, Configuration& configFile, QObject *parent)
   : QObject(parent)
   , LinkIf(connectionGroupName, configFile)
   , ui_If(0)
{
   moveToThread(&linkThread);
   connect(&linkThread, SIGNAL(started()), this, SLOT(SlotThreadStarted())); // on thread start
   connect(&linkThread, SIGNAL(finished()), this, SLOT(SlotThreadFinished())); // on thread stop
   connect(this, SIGNAL(SignalThreadTerminateRequest()), this, SLOT(SlotThreadTerminateRequest()), Qt::QueuedConnection);

   connect(this, SIGNAL(SignalSocketConnectRequest()), this, SLOT(SlotSocketConnectRequest()), Qt::QueuedConnection);
   connect(this, SIGNAL(SignalSocketDisconnectRequest()), this, SLOT(SlotSocketDisconnectRequest()), Qt::QueuedConnection);

}

void BaseLink::Connect()
{
   qInfo() << GetGroupName() + " connecting";
   emit SignalSocketConnectRequest();
}

void BaseLink::Disconnect()
{
   qInfo() << GetGroupName() + " disconnecting";
   emit SignalSocketDisconnectRequest();
}

void BaseLink::Start()
{
   qInfo() << GetGroupName() + " thread starting";
   linkThread.start();
}

void BaseLink::Stop()
{
   qInfo() << GetGroupName() + " thread stopping";
   emit SignalThreadTerminateRequest();
   linkThread.wait();
}

void BaseLink::SlotThreadStarted()
{
   qInfo() << GetGroupName() + " thread started";
   ThreadStarted();
}

void BaseLink::SlotThreadTerminateRequest()
{
   qInfo() << GetGroupName() + " thread termination request";
   ui_If = 0;
   SlotSocketDisconnectRequest();
   linkThread.quit();
}

void BaseLink::SlotThreadFinished()
{
   qInfo() << GetGroupName() + " thread stopped";
   ThreadFinished();
   SlotSocketDisconnectRequest();
}

void BaseLink::SlotSocketConnectRequest()
{
   qInfo() << GetGroupName() + " connect request";
   SocketConnectRequest();
}

void BaseLink::SlotSocketDisconnectRequest()
{
   qInfo() << GetGroupName() + " disconnect request";
   SocketDisconnectRequest();
}

void BaseLink::SlotSocketConnected()
{
   qInfo() << GetGroupName() + " connected";

   if (!ui_If) { return; }

   ui_If->LinkConnected();

   SocketConnected();
}

void BaseLink::SlotSocketDisconnected()
{
   qInfo() << GetGroupName() + " disconnected";

   if (!ui_If) { return; }

   ui_If->LinkDisconnected();

   SocketDisconnected();
}
