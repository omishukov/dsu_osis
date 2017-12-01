#ifndef OSISDATAQUEUE_H
#define OSISDATAQUEUE_H

#include <QObject>
#include <QQueue>
#include <QByteArray>
#include <QMutex>

class DataQueue : public QObject
{
   Q_OBJECT
public:
   DataQueue(QObject* parent = 0);
   ~DataQueue();

   void AddData(QByteArray* qba);
   bool GetData(QByteArray* qba);

signals:
   void NewData();

private:
   QQueue<QByteArray*> OsisData;
   QMutex M;
};

#endif // OSISDATAQUEUE_H
