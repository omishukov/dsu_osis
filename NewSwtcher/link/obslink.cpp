#include <QMutexLocker>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "obslink.h"

ObsLink::ObsLink(const QString &connectionGroupName, Configuration &configFile, QObject *parent)
   : BaseLink(connectionGroupName, configFile, parent)
   , obsWebSocketClient(0)
   , socketReconnectNeeded(false)
{
   const QMetaObject &mo = staticMetaObject;
   metaWSRequest = mo.enumerator(mo.indexOfEnumerator("WSRequest"));
   metaWSEvent = mo.enumerator(mo.indexOfEnumerator("WSEvent"));
}

void ObsLink::SlotSocketReadyRead(QString message)
{
   //qInfo() << " WS msg: " + message;

   QByteArray obsMsg = message.toUtf8();
   QJsonDocument obsData(QJsonDocument::fromJson(obsMsg));
   QJsonObject obsJsonData = obsData.object();

   if (obsJsonData.contains("update-type"))
   {
      QString updateType = obsJsonData["update-type"].toString();

      switch (metaWSEvent.keyToValue(updateType.toLocal8Bit().constData()))
      {
      case ProfileChanged:
         WsRequest(GetCurrentProfile);
         break;
      case SceneCollectionChanged:
         WsRequest(GetCurrentSceneCollection);
         break;
      case ScenesChanged:
         WsRequest(GetSceneList);
         break;
      default:
         qInfo() << " Unhandled Event: " + updateType;
         break;
      }
   }
   else if (obsJsonData.contains("message-id"))
   {
      QString messageId = obsJsonData["message-id"].toString();

      switch (metaWSRequest.keyToValue(messageId.toLocal8Bit().constData()))
      {
      case GetCurrentProfile:
         qInfo() << " Current Profile: " + obsJsonData["profile-name"].toString();
         break;
      case GetCurrentSceneCollection:
         qInfo() << " Current Scene Collection: " + obsJsonData["sc-name"].toString();
         break;
      case GetSceneList:
         {
            QJsonArray sceneArray = obsJsonData["scenes"].toArray();
            QStringList SceneList;
            for (int i = 0; i < sceneArray.size(); ++i)
            {
               QJsonObject obsJsonDataScene = sceneArray[i].toObject();
               SceneList << obsJsonDataScene["name"].toString();
            }
            qInfo() << " Current Scene List: " << SceneList;
         }
         break;
      default:
         qInfo() << " Unhandled Response: " + messageId;
         break;
      }
   }
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

   WsRequest(GetCurrentProfile);
   WsRequest(GetCurrentSceneCollection);
   WsRequest(GetSceneList);
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

void ObsLink::WsRequest(int key)
{
   QJsonObject reqObj;
   reqObj["message-id"] = metaWSRequest.valueToKey(key);
   reqObj["request-type"] = metaWSRequest.valueToKey(key);

   QJsonDocument sendReq(reqObj);
   obsWebSocketClient->sendTextMessage(sendReq.toJson());
}
