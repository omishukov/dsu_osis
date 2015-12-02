#include "osisdataprovider.h"
#include <QDomDocument>
#include <QtDebug>
#include <QMetaEnum>
#include "event.h"

OsisDataProvider::OsisDataProvider()
   : osisEvent(0)
{

}

OsisDataProvider::~OsisDataProvider()
{
   delete osisEvent;
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

         const QMetaObject &mo = OsisDataProvider::staticMetaObject;
         int index = mo.indexOfEnumerator("OsisMessageType");
         QMetaEnum metaEnum = mo.enumerator(index);

         switch(metaEnum.keyToValue(tagName.toLocal8Bit().constData()))
         {
            case Event_Overview:
            {
               if (!osisEvent)
               {
                  osisEvent = new OsisEvent();
               }
               osisEvent->AddEvent(e);
            }
            break;

            default:
            break;
         }

      }
      n = n.nextSibling();
   }
}

