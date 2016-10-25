#include <QDebug>
#include "dataparser.h"
#include "actiontoscene.h"

OsisParser::OsisParser(QObject *parent)
   : QObject(parent)
   , DataIf(0)
   , ObsDataSaver(0)
{

}

void OsisParser::SetObsDataSaver(Actions* obsData)
{
    ObsDataSaver = obsData;
    ObsDataSaver->SetOsisInfoIf(&Competition);
}

void OsisParser::ProcessData()
{
   QMutexLocker lock(&M);

   if (DataIf)
   {
      QByteArray* data = DataIf->GetData();
      if (data)
      {
         Handle(*data);
         delete data;
      }
   }
}

void OsisParser::Initialize()
{
   if (ObsDataSaver)
   {
      ObsDataSaver->SetLock(&M);
      connect(&Competition, SIGNAL(NewAction(int)), ObsDataSaver, SLOT(AddAction(int))); // Update UI
      connect(&Competition, SIGNAL(DoActions()), ObsDataSaver, SLOT(DoActions())); // Update UI
   }

}

void OsisParser::Uninit()
{

}

void OsisParser::Handle(QByteArray& qba)
{
   QByteArray osisData;
   osisData.swap(qba);
   osisData.prepend("<?xml version=\"1.0\" encoding=\"windows-1252\" ?>");

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

void OsisParser::ProcessOsisData(QDomNode& n)
{
   ProcessOsisTree(n);
   Competition.ProcessingDone();
}

bool OsisParser::ProcessOsisTree(QDomNode& n)
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

bool OsisParser::ProcessOsisElement(QDomNode& n)
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

   const QMetaObject &mo = OsisParser::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisXmlElements");
   QMetaEnum metaEnum = mo.enumerator(index);

   QString elementName = e.tagName();
   int xmlElementTag = metaEnum.keyToValue(elementName.toLocal8Bit().constData());
   switch(xmlElementTag)
   {
      case Isu_Osis:
         Competition.AddIsuOsis(new IsuOsis(e, elementName));
         break;
      case Event:
         Competition.AddEvent(new OsisEvent(e, elementName));
         break;
      case Segment_Start:
         Competition.AddSegmentStart(new OsisSegmentStart(e, elementName));
         break;
      case Category:
         Competition.AddCategory(new OsisCategory(e, elementName));
         break;
      case Segment:
         Competition.AddSegment(new OsisSegment(e, elementName));
         break;
      case Official:
         Competition.AddOfficial(new OsisOfficial(e, elementName));
         break;
      case Participant:
         Competition.AddParticipant(new OsisParticipant(e, elementName));
         break;
      case Athlete:
         Competition.AddAthlete(new OsisAthlete(e, elementName));
         break;
      case Criteria:
         Competition.AddCriteria(new OsisCriteria(e, elementName));
         break;
      case Deduction:
         Competition.AddDeduction(new OsisDeduction(e, elementName));
         break;
      case Majority_Deduction:
         Competition.AddMajorityDeduction(new OsisMajorityDeduction(e, elementName));
         break;
      case Performance:
         Competition.AddPerformance(new OsisPerformance(e, elementName));
         break;
      case Element:
         Competition.AddElement(new OsisElement(e, elementName));
         break;
      case Warmup_Group:
         Competition.AddWarmupGroup(new OsisWarmupGroup(e, elementName));
         break;
      case Segment_Running:
         Competition.AddSegmentRunning(new OsisSegmentRunning(e, elementName));
         break;
      case Action:
         Competition.AddAction(new OsisAction(e, elementName));
         break;
      case Prf_Details:
         Competition.AddPrfDetails(new OsisPrfDetails(e, elementName));
         break;
      case Prf_Ranking:
         Competition.AddPrfRanking(new OsisPrfRanking(e, elementName));
         break;
      case Element_List:
         Competition.AddElementList(new OsisElementList(e, elementName));
         break;
      case Event_Overview:
         Competition.Uninit();
         break;
      case Segment_Result_List:
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
