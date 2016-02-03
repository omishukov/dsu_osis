/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include <QDebug>
#include "osisxml.h"
#include "event.h"
#include "category.h"
#include "segmentstart.h"
#include "participant.h"
#include "segment.h"
#include "criteria.h"
#include "deduction.h"
#include "majoritydeduction.h"
#include "official.h"
#include "athlete.h"
#include "element/performance.h"

OsisXml::OsisXml(OsisCompetitionIf* competition, QObject* parent)
   : QObject(parent)
   , Competition(competition)
{
}

void OsisXml::ProcessOsisData(QDomNode& n)
{
   ProcessOsisTree(n);
   Competition->ProcessingDone();
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
         Competition->AddEvent(new OsisEvent(e));
         break;
      case Category:
         Competition->AddCategory(new OsisCategory(e));
         break;
      case Segment_Start:
         Competition->AddSegmentStart(new OsisSegmentStart(e));
         break;
      case Official:
         Competition->AddOfficial(new OsisOfficial(e));
         break;
      case Participant:
         Competition->AddParticipant(new OsisParticipant(e));
         break;
      case Segment:
         Competition->AddSegment(new OsisSegment(e));
         break;
      case Athlete:
         Competition->AddAthlete(new OsisAthlete(e));
         break;
      case Criteria:
         Competition->AddCriteria(new OsisCriteria(e));
         break;
      case Deduction:
         Competition->AddDeduction(new OsisDeduction(e));
         break;
      case Majority_Deduction:
         Competition->AddMajorityDeduction(new OsisMajorityDeduction(e));
         break;
      case Performance:
         Competition->AddPerformance(new OsisPerformance(e));
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

void OsisXml::DataInd(QByteArray& qba)
{
   QByteArray osisData;
   osisData.swap(qba);

   QDomDocument doc;
   QString errMsg;
   int errLine;
   int errColumn;
   if (!doc.setContent(osisData, &errMsg, &errLine, &errColumn))
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
   ProcessOsisData(n);
}


