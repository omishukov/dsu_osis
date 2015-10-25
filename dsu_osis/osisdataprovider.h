#ifndef OSISDATAPROVIDER_H
#define OSISDATAPROVIDER_H

#include <QByteArray>
#include "osisdataif.h"

class OsisDataProvider: public OsisDataIf
{
public:
   OsisDataProvider();

public:
   virtual void DataInd(class QByteArray& qba);
};

#endif // OSISDATAPROVIDER_H
