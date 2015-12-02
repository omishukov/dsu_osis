#include <QDomDocument>
#include <QMetaEnum>
#include "event.h"

OsisEvent::OsisEvent()
   : event_ID(-1)
{
}

OsisEvent::~OsisEvent()
{
}

void OsisEvent::AddEvent(const QDomElement &element)
{
   QDomNode child = element.firstChild();
   QDomNode::NodeType t = child.nodeType();
   if (t != QDomNode::ElementNode)
   {
      return; // Error
   }

   QDomElement e = child.toElement(); // try to convert the node to an element.
   if(e.isNull())
   {
      return; // Error
   }

   QString tagName = e.tagName();

   const QMetaObject &mo = OsisEvent::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisEventElements");
   QMetaEnum metaEnum = mo.enumerator(index);

   if(metaEnum.keyToValue(tagName.toLocal8Bit().constData()) != Event)
   {
      return; // Error
   }

   QDomNamedNodeMap attr = e.attributes();
   int size = attr.size();
   if (!size)
   {
      return; // Error
   }

   index = mo.indexOfEnumerator("OsisEventAttributes");
   metaEnum = mo.enumerator(index);

   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();

      switch (metaEnum.keyToValue(at.name().toLocal8Bit().constData()))
      {
         case ID:
            event_ID = at.value().toInt();
            break;
         case Name:
            event_Name = at.value();
            break;
         case Abbreviation:
            event_Abbreviation = at.value();
            break;
         case Type:
            event_Type = at.value();
            break;
         case CmpType:
            event_CmpType = at.value();
            break;
         case ExtDt:
            event_ExtDt = at.value();
            break;
         default:
            break;
      }
   }

}
