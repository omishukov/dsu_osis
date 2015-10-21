#ifndef CALCCONNECTIONTHREAD_H
#define CALCCONNECTIONTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QMutex>
#include <QSemaphore>

class CalcConnectionThread : public QThread
{
public:
   CalcConnectionThread(QObject *parent = 0);
   ~CalcConnectionThread();

    void establishConnection(const QString &hostName, quint16 port);
    void destroyConnection();
    void run() Q_DECL_OVERRIDE;

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    void Stop();

private:
    bool quit;
    QString IpAddress;
    quint16 IpPort;
    QTcpSocket OsisSocket;
    QMutex Mutex;
    QSemaphore WaitEvent;

};

#endif // CALCCONNECTIONTHREAD_H
