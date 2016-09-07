#ifndef ISUCALCLINKTHREAD_H
#define ISUCALCLINKTHREAD_H

#include <QObject>
#include <QTcpSocket>

class IsuCalcLinkThread : public QObject
{
   Q_OBJECT
public:
   IsuCalcLinkThread(QObject* parent = 0);

public slots:
   void ChangedSettings(const QString& hostName, quint16 port, uint reconnect);
   void Initialize();
   void Uninit();
   void Connected();
   void Disconnected();
   void ReadyRead();
   void SocketError();

private:
   QString HostName;
   quint16 Port;
   bool Reconnect;
   QTcpSocket Socket;

};

#endif // ISUCALCLINKTHREAD_H
