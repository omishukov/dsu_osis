#include "calcconnectionthread.h"

CalcConnectionThread::CalcConnectionThread(QObject *parent)
   : QThread(parent), quit(false)
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
      //SERVER. ToDO.
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

   while (!quit)
   {
      OsisSocket->connectToHost(IpAddress, IpPort);

      if (!OsisSocket->waitForConnected(500))
      {
         emit connecting();
         continue;
      }
      while (!quit)
      {
         WaitEvent.acquire();
         if (quit)
         {
            continue;
         }
      }
   }
   OsisSocket->disconnect();
   delete OsisSocket;
   OsisSocket = 0;
}

void CalcConnectionThread::connected()
{

}

void CalcConnectionThread::disconnected()
{

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
