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
   QDomElement docElem = doc.documentElement();

   QDomNode n = docElem.firstChild();
   while(!n.isNull())
   {
      QDomElement e = n.toElement(); // try to convert the node to an element.
      if(!e.isNull())
      {
         QString tagName = e.tagName();

         qDebug() << tagName << endl; // the node really is an element.
      }
      n = n.nextSibling();
   }
}

