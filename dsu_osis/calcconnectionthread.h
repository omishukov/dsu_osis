#ifndef CALCCONNECTIONTHREAD_H
#define CALCCONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMutex>
#include <QSemaphore>
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
   void handleConnectionError(QAbstractSocket::SocketError socketError);

private:
   void Stop();
   void ChangeState(ConnectState newstate);
   void processData(const QByteArray& qba);

private:
   bool quit;
   QString IpAddress;
   quint16 IpPort;
   QTcpSocket* OsisSocket;
   QMutex Mutex;
   QSemaphore WaitEvent;
   ConnectState state;
   QEventLoop* m_pEventLoop;
};

#endif // CALCCONNECTIONTHREAD_H
