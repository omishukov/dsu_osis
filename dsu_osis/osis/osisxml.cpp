/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include <QDebug>
#include "osisxml.h"
#include "element/category.h"
#include "element/segmentstart.h"
#include "element/participant.h"
#include "element/segment.h"
#include "element/criteria.h"
#include "element/deduction.h"
#include "element/majoritydeduction.h"
#include "element/official.h"
#include "element/athlete.h"
#include "element/performance.h"
#include "element/element.h"
#include "element/warmupgroup.h"
#include "element/prfranking.h"
#include "element/segmentrunning.h"
#include "element/action.h"
#include "element/prfdetails.h"
#include "element/event.h"
#include "element/isuosis.h"
#include "element/elementlist.h"
#include "obs/actions.h"

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
   int index = mo.indexOfEnumerator("OsisXmlElements");
   QMetaEnum metaEnum = mo.enumerator(index);

   QString elementName = e.tagName();
   int xmlElementTag = metaEnum.keyToValue(e.tagName().toLocal8Bit().constData());
   switch(xmlElementTag)
   {
      case Isu_Osis:
         Competition->AddIsuOsis(new IsuOsis(e, elementName));
         break;
      case Event:
         Competition->AddEvent(new OsisEvent(e, elementName));
         break;
      case Segment_Start:
         Competition->AddSegmentStart(new OsisSegmentStart(e, elementName));
         break;
      case Category:
         Competition->AddCategory(new OsisCategory(e, elementName));
         break;
      case Segment:
         Competition->AddSegment(new OsisSegment(e, elementName));
         break;
      case Official:
         Competition->AddOfficial(new OsisOfficial(e, elementName));
         break;
      case Participant:
         Competition->AddParticipant(new OsisParticipant(e, elementName));
         break;
      case Athlete:
         Competition->AddAthlete(new OsisAthlete(e, elementName));
         break;
      case Criteria:
         Competition->AddCriteria(new OsisCriteria(e, elementName));
         break;
      case Deduction:
         Competition->AddDeduction(new OsisDeduction(e, elementName));
         break;
      case Majority_Deduction:
         Competition->AddMajorityDeduction(new OsisMajorityDeduction(e, elementName));
         break;
      case Performance:
         Competition->AddPerformance(new OsisPerformance(e, elementName));
         break;
      case Element:
         Competition->AddElement(new OsisElement(e, elementName));
         break;
      case Warmup_Group:
         Competition->AddWarmupGroup(new OsisWarmupGroup(e, elementName));
         break;
      case Segment_Running:
         Competition->AddSegmentRunning(new OsisSegmentRunning(e, elementName));
         break;
      case Action:
         Competition->AddAction(new OsisAction(e, elementName));
         break;
      case Prf_Details:
         Competition->AddPrfDetails(new OsisPrfDetails(e, elementName));
         break;
      case Prf_Ranking:
         Competition->AddPrfRanking(new OsisPrfRanking(e, elementName));
         break;
      case Element_List:
         Competition->AddElementList(new OsisElementList(e, elementName));
         break;
      case Event_Overview:
         Competition->Uninit();
         Competition->ProcessAction(Actions::EVENT_OVERVIEW);
         break;
      case Segment_Result_List:
         Competition->ProcessAction(Actions::SEGMENT_RESULT_LIST);
         break;
      case Prf:
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

