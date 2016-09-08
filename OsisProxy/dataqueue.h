#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include <QObject>
#include <QByteArray>
#include <QQueue>
#include <QMutex>

class DataQueue : public QObject
{
   Q_OBJECT
public:
   DataQueue(QObject* parent = 0);
   ~DataQueue();

   void AddData(QByteArray* qba);

signals:
   void NewData();

private:
   QQueue<QByteArray*> OsisData;
   QMutex m;
};

#endif // DATAQUEUE_H
