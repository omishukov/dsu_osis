#include <QMetaEnum>
#include "segmentstart.h"

OsisSegmentStart::OsisSegmentStart(QObject *parent)
   : QObject(parent)
   , SS_Segment_ID(-1)
   , SS_Category_ID(-1)
   , SS_Segment_Index(-1)
   , SS_Starting_Participant(-1)
   , SS_Next_Participant(-1)
   , SS_LastFinished_Participant(-1)
{

}

OsisSegmentStart&OsisSegmentStart::operator=(const OsisSegmentStart& copy)
{
   if (this == &copy)
   {
      return *this;
   }
   if(copy.SS_Segment_ID != -1)
   {
      SS_Segment_ID = copy.SS_Segment_ID;
   }
   if(copy.SS_Category_ID != -1)
   {
      SS_Category_ID = copy.SS_Category_ID;
   }
   if(copy.SS_Segment_Index != -1)
   {
      SS_Segment_Index = copy.SS_Segment_Index;
   }
   if(copy.SS_Starting_Participant != -1)
   {
      SS_Starting_Participant = copy.SS_Starting_Participant;
   }
   if(copy.SS_Next_Participant != -1)
   {
      SS_Next_Participant = copy.SS_Next_Participant;
   }
   if(copy.SS_LastFinished_Participant != -1)
   {
      SS_LastFinished_Participant = copy.SS_LastFinished_Participant;
   }
   return *this;
}

bool OsisSegmentStart::ProcessSegmentStartAttributes(QDomElement& segmentStartElement)
{
   // Parse and save <Segment_Start> attributes
   QDomNamedNodeMap attr = segmentStartElement.attributes();
   int size = attr.size();
   if (!size)
   {
      return false; // Error
   }

   const QMetaObject &mo = OsisSegmentStart::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisSegmentStartAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);
   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();

      switch (metaEnum.keyToValue(at.name().toLocal8Bit().constData()))
      {
         case Category_ID:
            SS_Category_ID = at.value().toInt();
            break;
         case Segment_ID:
            SS_Segment_ID = at.value().toInt();
            break;
         case Segment_Index:
            SS_Segment_Index = at.value().toInt();
            break;
         case Starting_Participant:
            SS_Starting_Participant = at.value().toInt();
            break;
         case Next_Participant:
            SS_Next_Participant = at.value().toInt();
            break;
         case LastFinished_Participant:
            SS_LastFinished_Participant = at.value().toInt();
            break;
         default:
            break;
      }
   }
   return true;

}
