#include <QByteArray>
#include "osisdataproxy.h"

OsisDataProxy::OsisDataProxy(QObject *parent)
   : QObject(parent)
   , DataIf(0)
{

}

void OsisDataProxy::ProcessData()
{
   if (DataIf)
   {
      QByteArray* data = 0;
      do
      {
         data = DataIf->GetData();
      } while(data);
   }

}
