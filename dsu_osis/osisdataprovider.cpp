#include <QtDebug>
#include <QMetaEnum>
#include "osisdataprovider.h"
#include "osis/event.h"

OsisDataProvider::OsisDataProvider()
   : osisMsg(new OsisXml())
{

}

OsisDataProvider::~OsisDataProvider()
{
   delete osisMsg;
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

   if (!docElem.tagName().contains("Isu_Osis"))
   {
      qDebug() << "XML Parser Error: the message shall start with <Isu_Osis>" << endl;
      return;
   }

   QDomNode n = docElem.firstChild();
   osisMsg->ProcessOsisData(n);

#if 0
   while(!n.isNull())
   {
      QDomElement e = n.toElement(); // try to convert the node to an element.
      if(e.isNull())
      {
         // Warning: An empty element
         continue;
      }
      switch(metaEnum.keyToValue(e.tagName().toLocal8Bit().constData()))
      {
         case Event_Overview:
            ProcessEvent(e);
            break;
         case Segment_Start:
            ProcessSegmentStart(e);
            break;

         default:
            break;
      }

      n = n.nextSibling();
   }
#endif
}

