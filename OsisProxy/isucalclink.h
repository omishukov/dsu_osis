#ifndef ISUCALCLINKTHREAD_H
#define ISUCALCLINKTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QMutex>
#include "dataqueue.h"

class IsuCalcLink : public QObject
{
   Q_OBJECT
public:
   IsuCalcLink(QObject* parent = 0);
   ~IsuCalcLink();

   void SetDataIf(DataQueue* dataIf) { DataIf = dataIf; }

public slots:
   void ChangedSettings(const QString& hostName, quint16 port, uint reconnect);
   void Initialize();
   void Uninit();
   void Connected();
   void Disconnected();
   void ReadyRead();
   void ProcessData(QByteArray qba);
   void SocketError(QAbstractSocket::SocketError);
   void Establish();
   void StopConnection();
   void TimerExpired();

signals:
   void Established();
   void IsuCalcDisconnected();
   void Reconnecting();

private:
   QString HostName;
   quint16 Port;
   bool Reconnect;
   QTcpSocket* Socket;
   QTimer* Timer;
   bool IgnoreReconnect;
   DataQueue* DataIf;
   QByteArray RemainingQBA;
   QMutex m;


};

#endif // ISUCALCLINKTHREAD_H
