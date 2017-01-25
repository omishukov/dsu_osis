#ifndef ISUCALCLINKTHREAD_H
#define ISUCALCLINKTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QMutex>
#include <QThread>
#include "dataqueue.h"

class IsuCalcLink : public QObject
{
   Q_OBJECT
public:
   IsuCalcLink(DataQueue* dataIf, QObject* parent = 0);
   ~IsuCalcLink();

   void startThread();

public slots:
   void ChangedSettings(const QString& hostName, quint16 port, uint reconnect);
   void Initialize();
   void Uninit();
   void Connected();
   void Disconnected();
   void ReadyRead();
   void ProcessData(QByteArray qba);
   void SocketError(QAbstractSocket::SocketError err);
   void Establish();
   void StopConnection();
   void TimerExpired();

signals:
   void Established();
   void IsuCalcDisconnected();
   void Reconnecting();

private:
   void CancelConnection();

   QString HostName;
   quint16 Port;
   bool Reconnect;
   QTcpSocket m_Socket;
   QTimer* Timer;
   bool IgnoreReconnect;
   DataQueue* DataIf;
   QByteArray RemainingQBA;
   QMutex m;
   QThread CalcLinkThread;

};

#endif // ISUCALCLINKTHREAD_H
