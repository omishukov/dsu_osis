/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDateTime>
#include "calcconnectionthread.h"

const quint8 STX = 0x02;
const quint8 ETX = 0x03;

CalcConnectionThread::CalcConnectionThread(QObject *parent)
   : QThread(parent),
     quit(false),
     OsisSocket(0),
     state(DISCONNECTED),
     m_pEventLoop(0),
     osisData(0),
     StartPos(-1)
{
}

CalcConnectionThread::~CalcConnectionThread()
{
   Stop();
}

void CalcConnectionThread::setDataIf(OsisDataIf* osisDataIf)
{
   osisData = osisDataIf;
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
      qDebug() << "Connected to ISUCalcFS." << endl;
      m_pEventLoop = new QEventLoop();
      m_pEventLoop->exec();
   }

   qDebug() << "Disconnected from ISUCalcFS." << endl;
   OsisSocket->disconnectFromHost();
   OsisSocket->disconnect();
   delete OsisSocket;
   OsisSocket = 0;
   delete m_pEventLoop;
   m_pEventLoop = 0;

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
   qInfo() << qba << endl;
   processData(qba);
}

void CalcConnectionThread::processData(QByteArray& qba)
{
   for (int i = 0; i < qba.size(); i++)
   {
      if (qba.at(i) == STX)
      {
         if (StartPos != -1)
         {
            newdata.clear();
         }
         StartPos = i + 1;
      }
      else if (qba.at(i) == ETX)
      {
         if (StartPos != -1)
         {
            if (!newdata.isEmpty())
            {
               StartPos = 0;
            }
            newdata.append(qba.mid(StartPos, i-StartPos));

            osisData->DataInd(newdata);

            newdata.clear();
            StartPos = -1;
         }
      }
   }

   if (StartPos != -1) // ETX was not at the end
   {
      newdata = qba.mid(StartPos);
   }
}


void CalcConnectionThread::Stop()
{
   if (isRunning())
   {
      if (m_pEventLoop && m_pEventLoop->isRunning())
      {
         m_pEventLoop->exit();
      }
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
