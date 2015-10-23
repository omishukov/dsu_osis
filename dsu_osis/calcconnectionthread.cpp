#include "calcconnectionthread.h"
#include <winsock2.h>

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
   quit = false;
   start();
}

void CalcConnectionThread::abortConnection()
{
   Stop();
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

   connect(OsisSocket, SIGNAL(connected()),this, SLOT(connected()));
   connect(OsisSocket, SIGNAL(disconnected()),this, SLOT(disconnected()));
   connect(OsisSocket, SIGNAL(readyRead()),this, SLOT(readyRead()));

   ChangeState(CONNECTING);
   while (!quit)
   {
      OsisSocket->connectToHost(IpAddress, IpPort, QIODevice::ReadOnly);

      if (!OsisSocket->waitForConnected(1000))
      {
         ChangeState(CONNECTING);
         continue;
      }
      ChangeState(CONNECTED);

      while (state == CONNECTED)
      {
         WaitEvent.acquire();
         if (quit)
         {
            break;
         }
      }
   }

   OsisSocket->disconnectFromHost();
   OsisSocket->disconnect();
   delete OsisSocket;
   OsisSocket = 0;

   ChangeState(DISCONNECTED);
}

void CalcConnectionThread::runAsServer()
{

}

void CalcConnectionThread::connected()
{
   ChangeState(CONNECTED);
}

void CalcConnectionThread::disconnected()
{
   ChangeState(DISCONNECTED);
   WaitEvent.release();
}

void CalcConnectionThread::readyRead()
{

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

void CalcConnectionThread::ChangeState(ConnectState newstate)
{
   if (state != newstate)
   {
      state = newstate;
      emit UpdateConnectionState();
   }
}
