#include <QDebug>
#include "competitiondata.h"
#include "obs/actions.h"

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
{

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
   emit NewAction(Actions::SEGMENT_START);

   delete newSegmentStart;
}

void OsisCompetitionData::AddCategory(OsisCategory* newCategory)
{
   if (!newCategory)
   {
      return;
   }
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
   emit NewAction(Actions::PRF_RANKING);
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

   const QMetaObject &mo = Actions::staticMetaObject;
   int index = mo.indexOfEnumerator("ObsAction");
   QMetaEnum metaEnum = mo.enumerator(index);
   QString elementName = newAction->GetAttribute(OsisAction::Command);
   elementName = elementName.toUpper();
   elementName.prepend("ACTION_");
   int xmlElementTag = metaEnum.keyToValue(&elementName.toStdString()[0]);
   emit NewAction(xmlElementTag);
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
