/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "isucompetition.h"

IsuCompetition::IsuCompetition(Actions* actions)
   : Current_DB_ID(-1)
   , Current_Event(0)
   , Last_Category_Id(-1)
   , Last_Participant_Id(-1)
   , osisInfo(new OsisXml(this))
   , Current_Category_Id(-1)
   , Segment_Start(0)
   , Current_Segment_Id(-1)
   , Current_Participant(0)
   , Current_Action(0)
   , actionHandler(actions)
{
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
   delete Segment_Start;
   delete Current_Action;
   delete osisInfo;
   delete actionHandler;
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
   Last_Participant_Id = -1;
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
   if (!newEvent || newEvent->ID == -1)
   {
      return;
   }
   if (!Current_Event)
   {
      Current_Event = newEvent;
      return;
   }

   if (Current_Event->ID != newEvent->ID)
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
   Current_Category_Id = Segment_Start->CategoryId;

   Current_Segment_Id = Segment_Start->SegmentId;

   actionHandler->AddAction(Actions::SEGMENT_START);

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

   if (Segments.contains(newSegment->Id))
   {
      Segments.value(newSegment->Id)->Update(newSegment);
      delete newSegment;
   }
   else
   {
      Segments[newSegment->Id] = newSegment;
   }

   Segments.value(newSegment->Id)->CategoryId = Last_Category_Id;
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
   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Performance: " << newPerformance->GetAttribute(OsisPerformance::ID) << endl;
      return;
   }
//   if (Segments.contains(Current_Segment))
//   {
//      Segments[Current_Segment]->AddPerformance(newPerformance);
//   }
}

void IsuCompetition::AddElement(OsisElement* newElement)
{
   delete newElement;
}

void IsuCompetition::AddWarmupGroup(OsisWarmupGroup* newWarmupGroup)
{
   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Warmup_Group: " << newWarmupGroup->GetAttribute(OsisWarmupGroup::Index) << endl;
      return;
   }
//   if (Segments.contains(Current_Segment))
//   {
//      Segments[Current_Segment]->AddWarmupGroup(newWarmupGroup);
//   }
}

void IsuCompetition::AddPrfRanking(OsisPrfRanking* newPrfRanking)
{
   if (Current_Segment_Id == -1)
   {
      qCritical() << "Undefined Segment ID when processing Prf_Ranking: " << newPrfRanking->GetAttribute(OsisPrfRanking::TypeName) << endl;
      return;
   }
//   if (Segments.contains(Current_Segment))
//   {
//      Segments[Current_Segment]->AddPrfRanking(newPrfRanking);
//   }

   actionHandler->AddAction(Actions::PRF_RANKING);
}

void IsuCompetition::AddSegmentRunning(OsisSegmentRunning* newSegmentRunning)
{
   if (!newSegmentRunning)
   {
      return;
   }
   bool ok;
   int SegId = newSegmentRunning->GetAttribute(OsisSegmentRunning::Segment_ID).toInt(&ok);
   if (ok && Segments.contains(SegId))
   {
      Current_Segment_Id = SegId;
   }
   else
   {
      Current_Segment_Id = -1;
   }
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
      return;
   }
//   if (Segments.contains(Current_Segment))
//   {
//      Segments[Current_Segment]->AddPrfDetails(newPrfDetails);
//   }

}

void IsuCompetition::AddElementList(OsisElementList* newElementList)
{

}

void IsuCompetition::ProcessAction(int action)
{
   actionHandler->AddAction(action);
}

void IsuCompetition::ProcessingDone()
{
   actionHandler->DoActions();
}
