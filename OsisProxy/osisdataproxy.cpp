#include <QByteArray>
#include <QDomDocument>
#include <QDebug>
#include <QMetaEnum>
#include "osisdataproxy.h"
#include "element/action.h"

OsisDataProxy::OsisDataProxy(QObject *parent)
   : QObject(parent)
   , DataIf(0)
   , Tag(-1)
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
         if (data)
         {
            Handle (data);
         }
      } while(data);
   }

}

void OsisDataProxy::Handle(QByteArray* qba)
{
   Cache(qba);
   delete qba; // temporary
//   Distribute(qba);
}

void OsisDataProxy::Cache(QByteArray* qba)
{
   QDomDocument doc;
   QString errMsg;
   int errLine;
   int errColumn;
   if (!doc.setContent(*qba, &errMsg, &errLine, &errColumn))
   {
      qCritical() << "XML Parser Error " << errMsg << " (" << errLine << ":" << errColumn << ")" << endl;
      return;
   }
   QDomElement docElem = doc.documentElement();

   if (!docElem.tagName().contains("Isu_Osis"))
   {
      qCritical() << "XML Parser Error: the message shall start with <Isu_Osis>" << endl;
      return;
   }

   QDomNode n = docElem.firstChild();

   Tag = -1;
   if (ProcessOsisTree(n) && Tag != -1)
   {
      switch(Tag)
      {
         case Event_Overview:
         {
            EventOverview.clear();
            EventOverview.append(*qba);
            SegmentStart.clear();
            PrfRanking.clear();
            ActionIni.clear();
         }
            break;
         case Segment_Start:
         {
            SegmentStart.clear();
            if (!EventOverview.isEmpty())
            {
               SegmentStart.append(*qba);
            }
         }
            break;
         case Prf_Ranking:
         {
            PrfRanking.clear();
            if (!EventOverview.isEmpty() && !SegmentStart.isEmpty())
            {
               PrfRanking.append(*qba);
            }
         }
            break;
         case Action:
         {
            ActionIni.clear();
            if (!EventOverview.isEmpty() && !SegmentStart.isEmpty() && !PrfRanking.isEmpty())
            {
               ActionIni.append(*qba);
            }
         }
            break;
         default:
            break;
      }

   }

}

bool OsisDataProxy::ProcessOsisTree(QDomNode& n)
{
   if (!ProcessOsisElement(n))
   {
      return false;
   }
   QDomNode node = n.firstChild();

   while(!node.isNull() && ProcessOsisTree(node))
   {
      node = node.nextSibling();
   }
   return true;
}

bool OsisDataProxy::ProcessOsisElement(QDomNode& n)
{
   if (n.isNull() || (n.nodeType() != QDomNode::ElementNode))
   {
      return true;
   }

   QDomElement e = n.toElement();
   if(e.isNull())
   {
      // Warning: An empty element
      return true;
   }

   const QMetaObject &mo = OsisDataProxy::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisXmlElements");
   QMetaEnum metaEnum = mo.enumerator(index);

   QString elementName = e.tagName();
   int xmlElementTag = metaEnum.keyToValue(elementName.toLocal8Bit().constData());
   switch(xmlElementTag)
   {
      case Event_Overview:
      {
         Tag = xmlElementTag;
      }
         break;
      case Segment_Start:
      {
         Tag = xmlElementTag;
      }
         break;
      case Prf_Ranking:
      {
         Tag = xmlElementTag;
      }
         break;
      case Action:
      {
         OsisAction* action = new OsisAction(e, elementName);
         QString elementName = action->GetAttribute(OsisAction::Command);
         if (!QString::compare(elementName, "INI"))
         {
            Tag = xmlElementTag;
         }
      }
         break;
      default:
         break;
   }

   return true;
}
