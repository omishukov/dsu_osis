#include "websocketserver.h"

const QString serverName = "OsisWebsocketServer";

OsisWebsocketServer::OsisWebsocketServer(DataQueue *dataIf, QObject *parent)
   : QObject(parent)
   , DataIf(dataIf)
   , Wserver(serverName, QWebSocketServer::NonSecureMode, this)
{
   moveToThread(&WebsockThread);
   connect(DataIf, &DataQueue::NewData, this, &OsisWebsocketServer::NewData);
   connect(&WebsockThread, &QThread::started, this, &OsisWebsocketServer::Started);
   connect(&WebsockThread, &QThread::finished, this, &OsisWebsocketServer::Finished);
}

void OsisWebsocketServer::NewData()
{
   QMutexLocker lock(&M);

   if (DataIf)
   {
      QByteArray* data = 0;
      data = DataIf->GetData();
      if (data)
      {
         qDebug() << "New data";
         Handle (data);
      }
   }

}
