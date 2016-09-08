#include "isucalclink.h"

IsuCalcLink::IsuCalcLink(QObject* parent)
   : QObject(parent)
   , Port(0)
   , Reconnect(false)
   , Socket(0)
   , Timer(0)
   , IgnoreReconnect(false)
   , DataIf(0)
   , RemainingData(false)
{

}

IsuCalcLink::~IsuCalcLink()
{
}

void IsuCalcLink::ChangedSettings(const QString& hostName, quint16 port, uint reconnect)
{
   HostName = hostName;
   Port = port;
   Reconnect = reconnect?true:false;
}

void IsuCalcLink::Initialize()
{
   Socket = new QTcpSocket;
   connect(Socket, SIGNAL(connected()), this, SLOT(Connected()));
   connect(Socket, SIGNAL(disconnected()), this, SLOT(Disconnected()));
   connect(Socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
   connect(Socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(SocketError(QAbstractSocket::SocketError)));
   Timer = new QTimer;
   Timer->setSingleShot(true);
   connect(Timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
}

void IsuCalcLink::Uninit()
{
   StopConnection();
   delete Timer;
   Timer = 0;
   delete Socket;
   Socket = 0;
}

void IsuCalcLink::Connected()
{
   emit Established();
}

void IsuCalcLink::Disconnected()
{
   if (Reconnect && !IgnoreReconnect)
   {
      emit Reconnecting();
      Establish();
   }
   else
   {
      emit IsuCalcDisconnected();
      if (IgnoreReconnect)
      {
         IgnoreReconnect = false;
      }
   }
}

void IsuCalcLink::ReadyRead()
{
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::ConnectedState)
   {
//      QByteArray* qba = new QByteArray(Socket->readAll());
//      DataIf->AddData(qba);
       ProcessData(Socket->readAll());
   }
}

const quint8 STX = 0x02;
const quint8 ETX = 0x03;

void IsuCalcLink::ProcessData(QByteArray qba)
{
    // Frame1: s........es....es...
    // Frame2: ....................
    // Frame3: es
    // Frame4: ...es
    // Frame5: ...e
    int pos_STX = -1;
    int pos_ETX = -1;
    while (!qba.isEmpty())
    {
        pos_STX = qba.indexOf(STX);
        pos_ETX = qba.indexOf(ETX);

        if (RemainingData)
        {
            if (((pos_ETX != -1) && ((pos_STX == -1) || (pos_ETX < pos_STX))))
            {
                // Frame: ......E
                // Frame: ......ES....
                // Frame: ES......E
                QByteArray* Data = new QByteArray(RemainingQBA.append(qba.mid(0, pos_ETX + 1)));
                DataIf->AddData(Data);
                qba.remove(0, pos_ETX + 1);
                RemainingQBA.clear();
                RemainingData = false;
                continue;
            }
            if (pos_ETX == -1 && pos_STX == -1)
            {
                // Frame: .........
                QByteArray* Data = new QByteArray(RemainingQBA.append(qba));
                qba.clear();
                return;
            }
            if (pos_ETX == -1 && pos_STX != -1)
            {
                // Frame: ..S...E
                RemainingData = false;
                RemainingQBA.clear();
                qba.remove(0, pos_STX);
                continue;
            }
        }
        else
        {
            if (pos_STX != 0)
            {
                // Frame: ..S...E
                RemainingData = false;
                RemainingQBA.clear();
                qba.remove(0, pos_STX);
                continue;
            }
            if (pos_STX != -1 && pos_ETX != -1 && pos_ETX > pos_STX)
            {

            }
        }


        if (pos_STX == -1 || pos_STX > 0 )
        {
            // Handle first remaining data
            if (!RemainingData)
            {   // Discard data
                if (pos_ETX != -1)
                {
                    qba.remove(0, pos_ETX+1);
                }
                continue;
            }
        }

        if (pos_STX != -1 && pos_ETX != -1)
        {
            if (pos_STX > pos_ETX)
            { // Frame1: .....es...
              // Frame2: es
                if (!RemainingData)
                {   // Discard data
                    qba.remove(0, pos_ETX+1); continue;
                }
                else
                {
                    QByteArray* Data = new QByteArray(RemainingQBA.append(qba.mid(0, pos_ETX + 1)));
                    DataIf->AddData(Data);
                    qba.remove(0, pos_ETX + 1);
                    RemainingQBA.clear();
                    RemainingData = false;
                }
            }
            else if (pos_STX < pos_ETX)
            {
                if (pos_STX == 0)
                {
                    QByteArray* Data = new QByteArray(qba.mid(pos_STX, pos_ETX - pos_STX + 1));
                    DataIf->AddData(Data);
                    qba.remove(pos_STX, pos_ETX - pos_STX + 1);
                    continue;
                }
            }
        }
        if (pos_STX == -1)
        {
            // STX not found
            if (pos_ETX == -1)
            {
                // ETX not found. I.e. Frame2:
            }
        }
    }
}

void IsuCalcLink::SocketError(QAbstractSocket::SocketError /*err*/)
{
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::UnconnectedState && Reconnect)
   {
      Timer->start(2250);
   }
   else if (connState != QAbstractSocket::ConnectedState)
   {
      emit IsuCalcDisconnected();
   }
}

void IsuCalcLink::Establish()
{
   QTcpSocket::SocketState connState = Socket->state();
   if (connState == QAbstractSocket::UnconnectedState)
   {
      emit Reconnecting();
      Socket->connectToHost(HostName, Port, QIODevice::ReadOnly);
   }
}

void IsuCalcLink::StopConnection()
{
   Timer->stop();
   if (Socket->state() != QAbstractSocket::UnconnectedState)
   {
      IgnoreReconnect = true;
      Socket->disconnectFromHost();
      Socket->close();
   }
   else
   {
      emit IsuCalcDisconnected();
   }
}

void IsuCalcLink::TimerExpired()
{
   if (Reconnect)
   {
      Establish();
   }
   else
   {
      emit IsuCalcDisconnected();
   }
}
