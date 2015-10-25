#include "calcconnectionthread.h"
#include <winsock2.h>

const quint8 STX = 0x02;
const quint8 ETX = 0x03;

CalcConnectionThread::CalcConnectionThread(QObject *parent)
   : QThread(parent),
     quit(false),
     OsisSocket(0),
     state(DISCONNECTED)
{
}

CalcConnectionThread::~CalcConnectionThread()
{
   Stop();
}

void CalcConnectionThread::establishConnection(const QString &hostName, quint16 port)
{
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
         continue;
      }
      m_pEventLoop = new QEventLoop();
      m_pEventLoop->exec();
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
   Stop();
}

void CalcConnectionThread::readyRead()
{
   QByteArray qba = OsisSocket->readAll();
   if (qba.size() > 0)
   {
      qint32 posSTX = getFirstCharPosition(qba, STX);
      qint32 posETX = getFirstCharPosition(qba, ETX);

      if (posSTX >= 0 && posETX >= 0 && posETX > posSTX)
      {
         // Normal case
         QByteArray newdata = qba.mid(posSTX+1, posETX - posSTX -1);
      }
   }
}

qint32 CalcConnectionThread::getFirstCharPosition(QByteArray& qba, quint8 tag)
{
   for (int i = 0; i < qba.size(); i++)
   {
      if (qba.at(i) == tag)
      {
         return i;
      }
   }
   return -1;
}


void CalcConnectionThread::Stop()
{
   if (isRunning())
   {
      m_pEventLoop->exit();
      quit = true;

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
