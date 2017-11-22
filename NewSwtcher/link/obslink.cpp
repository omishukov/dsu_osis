#include <QUrl>
#include "obslink.h"

ObsLink::ObsLink(const QString &connectionGroupName, Configuration &configFile, QObject *parent)
   : BaseLink(connectionGroupName, configFile, parent)
{
}

void ObsLink::SlotSocketReadyRead()
{

}

void ObsLink::SlotSocketError(QAbstractSocket::SocketError error)
{

}

void ObsLink::SocketConnectRequest()
{
    connect(&obsWebSocketClient, &QWebSocket::connected, this, &BaseLink::SlotSocketConnected);
    connect(&obsWebSocketClient, &QWebSocket::disconnected, this, &BaseLink::SlotSocketDisconnected);
    connect(&obsWebSocketClient, &QWebSocket::textMessageReceived, this, &ObsLink::SlotSocketReadyRead);
    connect(&obsWebSocketClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SlotSocketError(QAbstractSocket::SocketError)));

    QString Url_path = "ws://";
    GetIpInfo(Host, Port);
    Url_path += Host;
    Url_path += ":";
    Url_path += Port;
    obsWebSocketClient.open(QUrl(Url_path));

}

void ObsLink::SocketDisconnectRequest()
{

}

void ObsLink::SocketConnected()
{

}

void ObsLink::SocketDisconnected()
{

}

