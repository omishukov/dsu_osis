#ifndef OSISDATAPROXY_H
#define OSISDATAPROXY_H

#include <QObject>
#include "dataqueue.h"

class OsisDataProxy : public QObject
{
   Q_OBJECT
public:
   explicit OsisDataProxy(QObject *parent = 0);

   void SetDataIf(DataQueue* dataIf) { DataIf = dataIf; }

signals:

public slots:
   void ProcessData();

private:
   DataQueue* DataIf;
};

#endif // OSISDATAPROXY_H
