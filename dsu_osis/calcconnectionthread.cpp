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
