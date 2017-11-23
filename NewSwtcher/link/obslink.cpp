#include <QMutexLocker>
#include <QUrl>
#include "obslink.h"

ObsLink::ObsLink(const QString &connectionGroupName, Configuration &configFile, QObject *parent)
   : BaseLink(connectionGroupName, configFile, parent)
   , obsWebSocketClient(0)
   , socketReconnectNeeded(false)
{
}

void ObsLink::SlotSocketReadyRead()
{

}

void ObsLink::SlotSocketError(QAbstractSocket::SocketError error)
{
   qInfo() << GetGroupName() + " Socket error: " << error;

   if (error == QAbstractSocket::RemoteHostClosedError)
   {
      socketReconnectNeeded = true;
   }
   else
   {
      Reconnect();
   }
}

void ObsLink::SocketConnectRequest()
{
   if (obsWebSocketClient)
   {
      SocketDisconnectRequest();
   }
   QMutexLocker lock(&M);

   obsWebSocketClient = new QWebSocket();
   connect(obsWebSocketClient, &QWebSocket::connected, this, &BaseLink::SlotSocketConnected);
   connect(obsWebSocketClient, &QWebSocket::disconnected, this, &BaseLink::SlotSocketDisconnected);
   connect(obsWebSocketClient, &QWebSocket::textMessageReceived, this, &ObsLink::SlotSocketReadyRead);
   connect(obsWebSocketClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotSocketError(QAbstractSocket::SocketError)));

   Reconnect();
}

void ObsLink::SocketDisconnectRequest()
{
   if (obsWebSocketClient)
   {
      disconnect(obsWebSocketClient, 0, 0, 0);
      if (obsWebSocketClient && obsWebSocketClient->state() == QAbstractSocket::ConnectedState)
      {
         obsWebSocketClient->close();
      }
      delete obsWebSocketClient;
      obsWebSocketClient = 0;

      SlotSocketDisconnected();
   }

}

void ObsLink::SocketConnected()
{
   socketReconnectNeeded = false;
}

void ObsLink::SocketDisconnected()
{
   if (socketReconnectNeeded)
   {
      socketReconnectNeeded = false;
      Reconnect();
   }
}

void ObsLink::Reconnect()
{
   GetIpInfo(Host, Port);
   obsWebSocketClient->open(QUrl("ws://" + Host + ":" + Port));
}

