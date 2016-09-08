#ifndef ISUCALCLINKTHREAD_H
#define ISUCALCLINKTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class IsuCalcLinkThread : public QObject
{
   Q_OBJECT
public:
   IsuCalcLinkThread(QObject* parent = 0);
   ~IsuCalcLinkThread();

public slots:
   void ChangedSettings(const QString& hostName, quint16 port, uint reconnect);
   void Initialize();
   void Uninit();
   void Connected();
   void Disconnected();
   void ReadyRead();
   void SocketError(QAbstractSocket::SocketError err);
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

};

#endif // ISUCALCLINKTHREAD_H
