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

bool DataQueue::GetData(QByteArray* qba)
{
   QMutexLocker lock(&M);

   if (!OsisData.isEmpty())
   {
      qba = OsisData.dequeue();
      return true;
   }
   return false;
}
