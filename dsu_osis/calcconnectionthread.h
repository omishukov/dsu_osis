#ifndef CALCCONNECTIONTHREAD_H
#define CALCCONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QEventLoop>
#include <QTextStream>
#include "osisdataif.h"

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

   void setDataIf(class OsisDataIf* osisDataIf);
   void establishConnection(const QString &hostName, quint16 port);
   void abortConnection();
   void destroyConnection();
   void run() Q_DECL_OVERRIDE;
   void runAsClient();
   void runAsServer();
   ConnectState GetState() { return state; }
   void processData(QByteArray& qba);

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
   OsisDataIf* osisData;
   QByteArray newdata;
   int StartPos;
};

#endif // CALCCONNECTIONTHREAD_H
