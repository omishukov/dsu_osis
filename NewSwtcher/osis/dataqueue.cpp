#include <QMutexLocker>
#include "osis/dataqueue.h"

DataQueue::DataQueue(QObject *parent)
   : QObject(parent)
{

}

DataQueue::~DataQueue()
{
   for (auto qba:OsisData)
   {
      delete qba;
   }
}

void DataQueue::AddData(QByteArray* qba)
{
   QMutexLocker lock(&M);

   OsisData.enqueue(qba);

   emit NewData();
}

QByteArray* DataQueue::GetData()
{
   QMutexLocker lock(&M);

   if (!OsisData.isEmpty())
   {
      return OsisData.dequeue();
   }
   return 0;
}
