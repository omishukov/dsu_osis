#include "osisdataprovider.h"

OsisDataProvider::OsisDataProvider()
{

}

void OsisDataProvider::DataInd(QByteArray& qba)
{
   QByteArray osisData;
   osisData.swap(qba);
}

