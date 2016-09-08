#include "dataqueue.h"

#include <QMutexLocker>

DataQueue::DataQueue(QObject* parent)
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
   QMutexLocker lock(&m);

   OsisData.enqueue(qba);

   emit NewData();
}
