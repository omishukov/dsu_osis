#include "osisdataprovider.h"
#include <QDomDocument>
#include <QtDebug>

OsisDataProvider::OsisDataProvider()
{

}

void OsisDataProvider::DataInd(QByteArray& qba)
{
   QByteArray osisData;
   osisData.swap(qba);

   QDomDocument doc;
   QString errMsg;
   int errLine;
   int errColumn;
   if (!doc.setContent(osisData, &errMsg, &errLine, &errColumn))
   {
      qDebug() << "XML Parser Error " << errMsg << " (" << errLine << ":" << errColumn << ")" << endl;
      return;
   }
}

