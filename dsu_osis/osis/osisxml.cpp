#include <QMetaEnum>
#include "osisxml.h"

OsisXml::OsisXml(QObject* parent)
   : QObject(parent)
{
}

void OsisXml::ProcessOsisData(QDomNode& n)
{
   ProcessOsisTree(n);
   event.ProcessingDone();
}

bool OsisXml::ProcessOsisTree(QDomNode& n)
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


bool OsisXml::ProcessOsisElement(QDomNode& n)
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

   const QMetaObject &mo = OsisXml::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisElements");
   QMetaEnum metaEnum = mo.enumerator(index);

   switch(metaEnum.keyToValue(e.tagName().toLocal8Bit().constData()))
   {
      case Event:
         return event.ProcessEvent(e);
      case Category:
         return event.ProcessCategory(e);
      case Segment_Start:
         return event.ProcessSegmentStart(e);
      case Official:
//         return event.ProcessOfficial(e);
      case Participant:
         return event.ProcessParticipant(e);
      case Segment:
         return event.ProcessSegment(e);
      case Athlete:
//         return event.ProcessAthlete(e);
      case Criteria:
         return event.ProcessCriteria(e);
      case Deduction:
         return event.ProcessDeduction(e);
      case Majority_Deduction:
//         return ProcessMajorityDeduction(e);
      case Performance:
//         return ProcessPerformance(e);
      case Element:
//         return ProcessElement(e);
      case Segment_Running:
//         return ProcessSegmentRunning(e);
      case Action:
//         return ProcessAction(e);
      case Prf_Details:
//         return ProcessPrfDetails(e);
      case Prf_Ranking:
//         return ProcessPrfRanking(e);
      case Element_List:
//         return ProcessElementList(e);
      case Prf:
//         return ProcessPrf(e);

      case Event_Overview:
      case Participant_List:
      case Category_List:
      case Event_Officials_List:
      case Category_Result_List:
      case Segment_List:
      case Coaches:
      case Athlete_List:
      case Criteria_List:
      case Deduction_List:
      case Majority_Deduction_List:
      case Segment_Official_List:
      case Segment_Start_List:
      case Planned_Element_List:
      case Segment_Result_List:
      case Segment_Statistic:
         break;
      default:
         break;
   }

   return true;
}


