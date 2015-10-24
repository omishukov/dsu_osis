#ifndef CALCCONNECTIONTHREAD_H
#define CALCCONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QEventLoop>

class CalcConnectionThread : public QThread
{
   Q_OBJECT
public:
   CalcConnectionThread(QObject *parent = 0);
   ~CalcConnectionThread();

   typedef enum
   {
      DISCONNECTED,
      CONNECTING,
      CONNECTED
   } ConnectState;

   void establishConnection(const QString &hostName, quint16 port);
   void abortConnection();
   void destroyConnection();
   void run() Q_DECL_OVERRIDE;
   void runAsClient();
   void runAsServer();
   ConnectState GetState() { return state; };

signals:
   void UpdateConnectionState();

public slots:
   void connected();
   void disconnected();
   void readyRead();

private:
   void Stop();
   void ChangeState(ConnectState newstate);
   qint32 getFirstCharPosition(QByteArray& qba, quint8 tag);


private:
   bool quit;
   QString IpAddress;
   quint16 IpPort;
   QTcpSocket* OsisSocket;
   ConnectState state;
   QEventLoop* m_pEventLoop;
};

#endif // CALCCONNECTIONTHREAD_H
