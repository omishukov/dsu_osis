/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "isucompetition.h"

//#include <windows.h>

IsuCompetition::IsuCompetition()
   : Current_DB_ID(-1)
   , Current_Event(0)
   , Last_Category_Id(-1)
   , Last_Participant_Id(-1)
   , Current_Performance_Result(0)
   , Current_Participant_Id(-1)
   , osisInfo(new OsisXml(this))
   , Current_Category_Id(-1)
   , Current_Segment_Id(-1)
   , Current_Action(0)
{
   actionHandler.SetOsisInfoIf(this);
}

IsuCompetition::~IsuCompetition()
{
   delete Current_Event;
   foreach (OsisParticipant* participant, Participants)
   {
      delete participant;
   }
   foreach (OsisSegment* segment, Segments)
   {
      delete segment;
   }
   foreach (OsisCategory* category, Categories)
   {
      delete category;
   }
   Categories.clear();
   delete Current_Action;
   delete osisInfo;
}

void IsuCompetition::Uninit()
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
   Current_Participant_Id = -1;

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

   for (auto official : Officials)
   {
      delete official;
   }

   WarmupGroups.clear();

   delete Current_Action;
   Current_Action = 0;

   delete Current_Performance_Result;
   Current_Performance_Result = 0;
}

QString IsuCompetition::GetCurrentSkaterName()
{
   int id = Current_Action->Current_Participant_Id;
   if (id == -1)
   {
      return QString();
   }
   return Participants[id]->GetAttribute(OsisParticipant::Short_Name);
}

QString IsuCompetition::GetEventName()
{
    return Current_Event->GetAttribute(OsisEvent::Name);
}

bool IsuCompetition::GetSegmentStartList(QMap<int, QList<QString> >& segmentStartList)
{
   for( auto performance : Performances)
   {
      int StartNum = performance->GetAttributeInt(OsisPerformance::Start_Number);
      if (StartNum == -1 || performance->Id == -1)
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

void IsuCompetition::AddIsuOsis(IsuOsis* newIsuOsis)
{
   if (Current_DB_ID == -1 || Current_DB_ID != newIsuOsis->DatabaseId)
   {
      Uninit();

      // Use Database ID to validate current Event
      Current_DB_ID = newIsuOsis->DatabaseId;
      delete newIsuOsis;
   }
}

void IsuCompetition::AddEvent(OsisEvent* newEvent)
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
   }
}

void IsuCompetition::AddSegmentStart(OsisSegmentStart* newSegmentStart)
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
   actionHandler.AddAction(Actions::SEGMENT_START);
   delete newSegmentStart;
}

void IsuCompetition::AddCategory(OsisCategory* newCategory)
{
   if (!newCategory)
   {
      return;
   }
   if (newCategory->Id == -1)
   {
      delete newCategory;
      return;
   }

   Last_Category_Id = newCategory->Id;

   if (Categories.contains(Last_Category_Id))
   {
      Categories.value(Last_Category_Id)->Update(newCategory);
      delete newCategory;
   }
   else
   {
      Categories[Last_Category_Id] = newCategory;
   }
}

void IsuCompetition::AddSegment(OsisSegment* newSegment)
{
   if (!newSegment)
   {
      return;
   }
   if (newSegment->Id == -1 || Last_Category_Id == -1)
   {
      qCritical() << "Undefined Category when processing Segment ID: " << newSegment->GetAttribute(OsisSegment::ID) << endl;
      delete newSegment;
      return;
   }

   int key = newSegment->Id;
   if (Segments.contains(key))
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

void IsuCompetition::AddParticipant(OsisParticipant* newParticipant)
{
   if (!newParticipant)
   {
      return;
   }
   if (newParticipant->Id == -1)
   {
      delete newParticipant;
      return;
   }

   Last_Participant_Id = newParticipant->Id;

   if (Participants.contains(Last_Participant_Id))
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

void IsuCompetition::AddCriteria(OsisCriteria* newCriteria)
{
   delete newCriteria;
}

void IsuCompetition::AddDeduction(OsisDeduction* newDeduction)
{
   delete newDeduction;
}

void IsuCompetition::AddMajorityDeduction(OsisMajorityDeduction* newMajorityDeduction)
{
   delete newMajorityDeduction;
}

void IsuCompetition::AddOfficial(OsisOfficial* newOfficial)
{
   delete newOfficial;
}

void IsuCompetition::AddAthlete(OsisAthlete* newAthlete)
{
   delete newAthlete;
}

void IsuCompetition::AddPerformance(OsisPerformance* newPerformance)
{
   if (!newPerformance)
   {
      return;
   }
   if (newPerformance->Id == -1 || Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Performance: " << newPerformance->GetAttribute(OsisPerformance::ID) << endl;
      delete newPerformance;
      return;
   }
   int key = newPerformance->Id;
   if (Performances.contains(key))
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

void IsuCompetition::AddElement(OsisElement* newElement)
{
   delete newElement;
}

void IsuCompetition::AddWarmupGroup(OsisWarmupGroup* newWarmupGroup)
{
   if (!newWarmupGroup)
   {
      return;
   }
   if (newWarmupGroup->Ind == -1 || newWarmupGroup->Num == 0)
   {
      delete newWarmupGroup;
      return;
   }
   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Warmup_Group: " << newWarmupGroup->GetAttribute(OsisWarmupGroup::Index) << endl;
      return;
   }

   int key = newWarmupGroup->Ind;
      if (WarmupGroups.contains(key))
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

void IsuCompetition::AddPrfRanking(OsisPrfRanking* newPrfRanking)
{
   delete newPrfRanking;
   actionHandler.AddAction(Actions::PRF_RANKING);
}

void IsuCompetition::AddSegmentRunning(OsisSegmentRunning* newSegmentRunning)
{
   if (!newSegmentRunning)
   {
      return;
   }
   Current_Segment_Id = newSegmentRunning->SegmentID;

   delete newSegmentRunning;
}

void IsuCompetition::AddAction(OsisAction* newAction)
{
   if (!newAction)
   {
      return;
   }
   if (Current_Action)
   {
      delete Current_Action;
   }
   Current_Action = newAction;

   const QMetaObject &mo = Actions::staticMetaObject;
   int index = mo.indexOfEnumerator("ObsAction");
   QMetaEnum metaEnum = mo.enumerator(index);

   QString elementName = newAction->GetAttribute(OsisAction::Command);
   elementName = elementName.toUpper();
   elementName.prepend("ACTION_");
   int xmlElementTag = metaEnum.keyToValue(&elementName.toStdString()[0]);
   ProcessAction(xmlElementTag);
}

void IsuCompetition::AddPrfDetails(OsisPrfDetails* newPrfDetails)
{
   if (!newPrfDetails)
   {
      return;
   }

   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Prf_Details" << endl;
      delete newPrfDetails;
      return;
   }
   delete Current_Performance_Result;
   Current_Performance_Result = newPrfDetails;
}

void IsuCompetition::AddElementList(OsisElementList* newElementList)
{
   delete newElementList;
}

void IsuCompetition::ProcessAction(int action)
{
   actionHandler.AddAction(action);
}

void IsuCompetition::ProcessingDone()
{
   actionHandler.DoActions();
//   Sleep(100);
}
