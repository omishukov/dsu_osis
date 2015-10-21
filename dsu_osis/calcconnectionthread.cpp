#include "calcconnectionthread.h"

CalcConnectionThread::CalcConnectionThread(QObject *parent)
   : QThread(parent),
     quit(false),
     state(DISCONNECTED)
{
}

CalcConnectionThread::~CalcConnectionThread()
{
   Stop();
}

void CalcConnectionThread::establishConnection(const QString &hostName, quint16 port)
{
   QMutexLocker locker(&Mutex);
   Stop();
   IpAddress = hostName;
   IpPort = port;
   start();
}

void CalcConnectionThread::destroyConnection()
{

}

void CalcConnectionThread::run()
{
   if (IpAddress != "")
   {
      runAsClient();
   }
   else
   {
      runAsServer();
   }

}

void CalcConnectionThread::runAsClient()
{
   if (OsisSocket)
   {
      delete OsisSocket;
   }

   OsisSocket = new QTcpSocket;

   connect(OsisSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleConnectionError(QAbstractSocket::SocketError)));
   connect(OsisSocket, SIGNAL(connected()),this, SLOT(connected()));
   connect(OsisSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
   connect(OsisSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));

   while (!quit)
   {
      state = CONNECTING;
      OsisSocket->connectToHost(IpAddress, IpPort, QIODevice::ReadOnly);

      if (!OsisSocket->waitForConnected(10000))
      {
         QAbstractSocket::SocketError err = OsisSocket->error();
         emit UpdateConnectionState();
         continue;
      }
      while (state == CONNECTED)
      {
         WaitEvent.acquire();
         if (quit)
         {
            continue;
         }
      }
   }
   OsisSocket->disconnectFromHost();
   OsisSocket->disconnect();
   delete OsisSocket;
   OsisSocket = 0;
}

void CalcConnectionThread::runAsServer()
{

}

void CalcConnectionThread::connected()
{
   state = CONNECTED;
   emit UpdateConnectionState();
}

void CalcConnectionThread::disconnected()
{
   state = DISCONNECTED;
   WaitEvent.release();
   emit UpdateConnectionState();
}

void CalcConnectionThread::readyRead()
{

}

void CalcConnectionThread::handleConnectionError(QAbstractSocket::SocketError socketError)
{
   switch (socketError) {
   case QAbstractSocket::RemoteHostClosedError:
       break;
   case QAbstractSocket::HostNotFoundError:
       break;
   case QAbstractSocket::ConnectionRefusedError:
       break;
   default:
       QString tcpError = OsisSocket->errorString();
       break;
   }
}

void CalcConnectionThread::Stop()
{
   if (isRunning())
   {
      quit = true;
      if (!WaitEvent.tryAcquire())
      {
         WaitEvent.release();
      }
      if (!wait(3000))
      {
         terminate();
      }
   }
}
