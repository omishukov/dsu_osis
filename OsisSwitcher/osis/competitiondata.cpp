#include <QDebug>
#include "competitiondata.h"
#include "actiontoscene.h"

OsisCompetitionData::OsisCompetitionData(QObject *parent)
   : QObject(parent)
   , Current_DB_ID(-1)
   , Current_Event(0)
   , Current_Category_Id(-1)
   , Current_Segment_Id(-1)
   , Last_Category_Id(-1)
   , Last_Participant_Id(-1)
   , Current_Action(0)
   , Current_Performance_Result(0)
   , CurrentParticipantId(-1)
{

}

OsisCompetitionData::~OsisCompetitionData()
{
   Uninit();

}

void OsisCompetitionData::AddIsuOsis(IsuOsis* newIsuOsis)
{
   if (Current_DB_ID == -1 || Current_DB_ID != newIsuOsis->DatabaseId)
   {
      Uninit();

      // Use Database ID to validate current Event
      Current_DB_ID = newIsuOsis->DatabaseId;
   }
   delete newIsuOsis;
}

void OsisCompetitionData::AddEvent(OsisEvent* newEvent)
{
   if (!newEvent)
   {
      return;
   }
   if (newEvent->Id == -1)
   {
      delete newEvent;
      return;
   }

   if (!Current_Event)
   {
      Current_Event = newEvent;
      return;
   }

   if (Current_Event->Id != newEvent->Id)
   {
      Uninit();
      Current_Event = newEvent;
   }
   else
   {
      Current_Event->Update(newEvent);
      delete newEvent;
   }
}

void OsisCompetitionData::AddSegmentStart(OsisSegmentStart* newSegmentStart)
{
   if (!newSegmentStart)
   {
      return;
   }
   if (newSegmentStart->CategoryId == -1 || newSegmentStart->SegmentId == -1)
   {
      delete newSegmentStart;
      return;
   }

   Current_Category_Id = newSegmentStart->CategoryId;
   Current_Segment_Id = newSegmentStart->SegmentId;

   delete newSegmentStart;
}

void OsisCompetitionData::AddCategory(OsisCategory* newCategory)
{
   if (!newCategory) { return; }

   if (newCategory->Id == -1)
   {
      delete newCategory;
      newCategory = 0;
      return;
   }

   Last_Category_Id = newCategory->Id;

   if (!Categories.isEmpty() && Categories.contains(Last_Category_Id))
   {
      Categories.value(Last_Category_Id)->Update(newCategory);
      delete newCategory;
   }
   else
   {
      Categories[Last_Category_Id] = newCategory;
   }
}

void OsisCompetitionData::AddSegment(OsisSegment* newSegment)
{
   if (!newSegment) { return; }

   if (newSegment->Id == -1 || Last_Category_Id == -1)
   {
      qCritical() << "Undefined Category when processing Segment ID: " << newSegment->GetAttribute(OsisSegment::ID) << endl;
      delete newSegment;
      return;
   }

   int key = newSegment->Id;
   if (!Segments.isEmpty() && Segments.contains(key))
   {
      Segments.value(key)->Update(newSegment);
      delete newSegment;
   }
   else
   {
      Segments[key] = newSegment;
   }

   Segments.value(key)->CategoryId = Last_Category_Id;
}

void OsisCompetitionData::AddParticipant(OsisParticipant* newParticipant)
{
   if (!newParticipant) { return; }

   if (newParticipant->Id == -1)
   {
      delete newParticipant;
      return;
   }

   Last_Participant_Id = newParticipant->Id;

   if (!Participants.isEmpty() && Participants.contains(Last_Participant_Id))
   {
      Participants.value(Last_Participant_Id)->Update(newParticipant);
      delete newParticipant;
   }
   else
   {
      Participants[Last_Participant_Id] = newParticipant;
   }

   Participants.value(Last_Participant_Id)->CategoryId = Last_Category_Id;
}

void OsisCompetitionData::AddCriteria(OsisCriteria* newCriteria)
{
   delete newCriteria;
}

void OsisCompetitionData::AddDeduction(OsisDeduction* newDeduction)
{
   delete newDeduction;
}

void OsisCompetitionData::AddMajorityDeduction(OsisMajorityDeduction* newMajorityDeduction)
{
   delete newMajorityDeduction;
}

void OsisCompetitionData::AddOfficial(OsisOfficial* newOfficial)
{
   delete newOfficial;
}

void OsisCompetitionData::AddAthlete(OsisAthlete* newAthlete)
{
   delete newAthlete;
}

void OsisCompetitionData::AddPerformance(OsisPerformance* newPerformance)
{
   if (!newPerformance) { return; }

   if (newPerformance->Id == -1 || Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Performance: " << newPerformance->GetAttribute(OsisPerformance::ID) << endl;
      delete newPerformance;
      return;
   }
   int key = newPerformance->Id;
   if (!Performances.isEmpty() && Performances.contains(key))
   {
      Performances.value(key)->Update(newPerformance);
      delete newPerformance;
   }
   else
   {
      Performances[key] = newPerformance;
   }
   Performances.value(key)->SegmentId = Current_Segment_Id;
}

void OsisCompetitionData::AddElement(OsisElement* newElement)
{
   delete newElement;
}

void OsisCompetitionData::AddWarmupGroup(OsisWarmupGroup* newWarmupGroup)
{
   if (!newWarmupGroup) { return; }

   if (newWarmupGroup->Ind == -1 || newWarmupGroup->Num == 0)
   {
      delete newWarmupGroup;
      return;
   }
   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Warmup_Group: " << newWarmupGroup->GetAttribute(OsisWarmupGroup::Index) << endl;
      delete newWarmupGroup;
      return;
   }

   int key = newWarmupGroup->Ind;
   if (!WarmupGroups.isEmpty() && WarmupGroups.contains(key))
   {
      WarmupGroups.value(key)->Update(newWarmupGroup);
      delete newWarmupGroup;
   }
   else
   {
      WarmupGroups[key] = newWarmupGroup;
   }
   WarmupGroups.value(key)->SegmentId = Current_Segment_Id;
}

void OsisCompetitionData::AddPrfRanking(OsisPrfRanking* newPrfRanking)
{
   delete newPrfRanking;
}

void OsisCompetitionData::AddSegmentRunning(OsisSegmentRunning* newSegmentRunning)
{
   if (!newSegmentRunning) { return; }

   Current_Segment_Id = newSegmentRunning->SegmentID;

   delete newSegmentRunning;
}

void OsisCompetitionData::AddAction(OsisAction* newAction)
{
   if (!newAction) { return; }

   delete Current_Action;
   Current_Action = newAction;

   if (Current_Action->Current_Participant_Id != -1)
   {
      CurrentParticipantId = Current_Action->Current_Participant_Id;
   }

   const QMetaObject &mo = ActionToScene::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisActionCommand");
   QMetaEnum metaEnum = mo.enumerator(index);
   QString elementName = newAction->GetAttribute(OsisAction::Command);
   elementName = elementName.toUpper();
   elementName.prepend("ACTION_");
   int xmlElementTag = metaEnum.keyToValue(&elementName.toStdString()[0]);
   emit NewAction(xmlElementTag);
   if (xmlElementTag == ActionToScene::ACTION_STP)
   {
      delete Current_Action;
      Current_Action = 0;
      CurrentParticipantId = -1;
   }
}

void OsisCompetitionData::AddPrfDetails(OsisPrfDetails* newPrfDetails)
{
   if (!newPrfDetails) { return; }

   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Prf_Details" << endl;
      delete newPrfDetails;
      return;
   }
   delete Current_Performance_Result;
   Current_Performance_Result = newPrfDetails;
}

void OsisCompetitionData::AddElementList(OsisElementList* newElementList)
{
   delete newElementList;
}

void OsisCompetitionData::ProcessingDone()
{
   emit DoActions();
}

void OsisCompetitionData::Uninit()
{
   delete Current_Event;
   Current_Event = 0;

   foreach (OsisCategory* category, Categories)
   {
      delete category;
   }
   Categories.clear();
   Current_Category_Id = -1;
   Last_Category_Id = -1;

   foreach (OsisSegment* segment, Segments)
   {
      delete segment;
   }
   Segments.clear();
   Current_Segment_Id = -1;

   foreach (OsisParticipant* participant, Participants)
   {
      delete participant;
   }
   Participants.clear();
   Last_Participant_Id = -1;

   foreach (OsisPerformance* performance, Performances)
   {
      delete performance;
   }
   Performances.clear();

   foreach (OsisWarmupGroup* warmup, WarmupGroups)
   {
      delete warmup;
   }
   WarmupGroups.clear();

//   for (auto official : Officials)
//   {
//      delete official;
//   }

   WarmupGroups.clear();

   delete Current_Action;
   Current_Action = 0;

   delete Current_Performance_Result;
   Current_Performance_Result = 0;

   CurrentParticipantId = -1;
}

QString OsisCompetitionData::GetCurrentSkaterName()
{
   if (CurrentParticipantId == -1 || !Participants.contains(CurrentParticipantId))
   {
      return QString();
   }
   return Participants[CurrentParticipantId]->GetAttribute(OsisParticipant::Short_Name);
}

QString OsisCompetitionData::GetCurrentSkaterNumber()
{
   if (!Current_Action)
   {
      return QString();
   }
   return Current_Action->GetAttribute(OsisAction::Current_Start_Number);
}

QString OsisCompetitionData::GetCurrentSkaterNation()
{
   if (!Current_Action)
   {
      return QString();
   }
   if (CurrentParticipantId == -1 || !Participants.contains(CurrentParticipantId))
   {
      return QString();
   }
   return Participants[CurrentParticipantId]->GetAttribute(OsisParticipant::Nation);
}

QString OsisCompetitionData::GetCurrentSkaterClub()
{
   if (!Current_Action)
   {
      return QString();
   }
   if (CurrentParticipantId == -1 || !Participants.contains(CurrentParticipantId))
   {
      return QString();
   }
   return Participants[CurrentParticipantId]->GetAttribute(OsisParticipant::Club);
}

QString OsisCompetitionData::GetEventName()
{
   return Current_Event->GetAttribute(OsisEvent::Name);
}

QString OsisCompetitionData::GetEventAbbreviation()
{
   return Current_Event->GetAttribute(OsisEvent::Abbreviation);
}

QString OsisCompetitionData::GetSegmentName()
{
   if (Current_Segment_Id == -1 || !Segments.contains(Current_Segment_Id))
   {
      return QString();
   }
   return Segments[Current_Segment_Id]->GetAttribute(OsisSegment::Name);
}

QString OsisCompetitionData::GetCategoryName()
{
   if (Current_Category_Id == -1 || !Categories.contains(Current_Category_Id))
   {
      return QString();
   }
   return Categories[Current_Category_Id]->GetAttribute(OsisCategory::Name);
}

bool OsisCompetitionData::GetSegmentStartList(QMap<int, QList<QString> >& segmentStartList)
{
   for( auto performance : Performances)
   {
      int StartNum = performance->GetAttributeInt(OsisPerformance::Start_Number);
      if (StartNum == -1 || performance->Id == -1 || !Participants.contains(performance->Id))
      {
         continue;
      }
      QList<QString> NameAndClub;
      NameAndClub << Participants[performance->Id]->GetAttribute(OsisParticipant::Short_Name) <<
                     Participants[performance->Id]->GetAttribute(OsisParticipant::Nation);

      segmentStartList[StartNum] = NameAndClub;
   }
   return true;
}

int OsisCompetitionData::CurrentStartNumber()
{
   QString stNum = GetCurrentSkaterNumber();
   if (stNum.isEmpty())
   {
      return 0;
   }
   return stNum.toInt();
}

bool OsisCompetitionData::GetWarmUpStartList(QMap<int, QList<QString> >& warmUpStartList)
{
   int stnum = CurrentStartNumber();
   if (!stnum)
   {
      return false;
   }
   QList<int> wupGroups;
   GetWarmUpGroupsList(wupGroups);

   int prev = 0;
   for (auto wupNum:wupGroups)
   {
      if (stnum <= wupNum)
      {
         for( auto performance : Performances)
         {
            int StartNum = performance->GetAttributeInt(OsisPerformance::Start_Number);
            if (StartNum == -1 || performance->Id == -1 || StartNum <= prev || StartNum > wupNum || !Participants.contains(performance->Id))
            {
               continue;
            }
            QList<QString> NameAndClub;
            NameAndClub << Participants[performance->Id]->GetAttribute(OsisParticipant::Short_Name) <<
                           Participants[performance->Id]->GetAttribute(OsisParticipant::Nation);

            warmUpStartList[StartNum] = NameAndClub;
         }
         break;
      }
      prev = wupNum;
   }
   return true;
}

QString OsisCompetitionData::GetCurrentWarmUpGroupNumber()
{
   int stnum = CurrentStartNumber();
   if (!stnum)
   {
      return QString();
   }

   QList<int> wupGroups;
   GetWarmUpGroupsList(wupGroups);

   int i = 1;
   for (auto wupNum:wupGroups)
   {
      if (stnum <= wupNum)
      {
         break;
      }
      i++;
   }
   return QString::number(i);
}

void OsisCompetitionData::GetWarmUpGroupsList(QList<int>& WarmUpList)
{
   WarmUpList.clear();
   int pNum = 0;
   for (auto wup:WarmupGroups)
   {
      pNum += wup->Num;
      WarmUpList.append(pNum);
   }
}

bool OsisCompetitionData::GetSegmentResultList(QMap<int, QList<QString> >& segmentResultList)
{
   int Rank;
   for( auto performance : Performances)
   {
      Rank = performance->GetAttributeInt(OsisPerformance::Rank);
      if (Rank == -1 || performance->Id == -1 || !Participants.contains(performance->Id))
      {
         continue;
      }
      QList<QString> NameClubPoints;
      NameClubPoints << Participants[performance->Id]->GetAttribute(OsisParticipant::Short_Name) <<
                     Participants[performance->Id]->GetAttribute(OsisParticipant::Nation) <<
                     performance->GetAttribute(OsisPerformance::Points);

      segmentResultList[Rank] = NameClubPoints;
   }
   return true;
}

QString OsisCompetitionData::GetPoints()
{
   if (Current_Performance_Result)
   {
      return Current_Performance_Result->GetAttribute(OsisPrfDetails::Points);
   }
   return QString();
}

QString OsisCompetitionData::GetTES()
{
   if (Current_Performance_Result)
   {
      return Current_Performance_Result->GetAttribute(OsisPrfDetails::TES);
   }
   return QString();
}

QString OsisCompetitionData::GetTCS()
{
   if (Current_Performance_Result)
   {
      return Current_Performance_Result->GetAttribute(OsisPrfDetails::TCS);
   }
   return QString();
}

QString OsisCompetitionData::GetBonus()
{
   if (Current_Performance_Result)
   {
      return Current_Performance_Result->GetAttribute(OsisPrfDetails::Bonus);
   }
   return QString();
}

QString OsisCompetitionData::GetDeduction()
{
   if (Current_Performance_Result)
   {
      return Current_Performance_Result->GetAttribute(OsisPrfDetails::Ded_Sum);
   }
   return QString();
}

QString OsisCompetitionData::GetRank()
{
   if (!Current_Action) { return QString(); }

   for( auto performance : Performances)
   {
      if (performance->Id == CurrentParticipantId)
      {
         return performance->GetAttribute(OsisPerformance::Rank);
      }
   }
   return QString();
}
