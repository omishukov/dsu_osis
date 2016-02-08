/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include "isucompetition.h"

IsuCompetition::IsuCompetition()
   : osisInfo(new OsisXml(this))
   , Event(0)
   , Current_Category(-1)
   , Segment_Start(0)
   , Current_Segment(-1)
   , Current_Participant(0)
   , Current_Action(0)
{

}

IsuCompetition::~IsuCompetition()
{
   delete Event;
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
   delete Segment_Start;
   delete Current_Action;
}

void IsuCompetition::AddEvent(OsisEvent* newEvent)
{
   Event = newEvent;
}

void IsuCompetition::AddCategory(OsisCategory* newCategory)
{
   Current_Category = newCategory->GetId();
   if (Current_Category == -1)
   {
      return;
   }

   if (Categories.contains(Current_Category))
   {
      Categories.value(Current_Category)->Update(*newCategory);
      delete newCategory;
   }
   else
   {
      Categories[Current_Category] = newCategory;
   }
}

void IsuCompetition::AddSegmentStart(OsisSegmentStart* newSegmentStart)
{
   bool ok;

   Segment_Start = newSegmentStart;
   Current_Category = Segment_Start->GetAttribute(OsisSegmentStart::Category_ID).toInt(&ok);
   if (!ok)
   {
      Current_Category = -1;
      qCritical() << "Wrong Category_ID in <Segment_Start>: " << Segment_Start->GetAttribute(OsisSegmentStart::Category_ID) << endl;
      return;
   }
   Current_Segment = Segment_Start->GetAttribute(OsisSegmentStart::Segment_ID).toInt(&ok);
   if (!ok)
   {
      Current_Segment = -1;
      qCritical() << "Wrong Segment_ID in <Segment_Start>: " << Segment_Start->GetAttribute(OsisSegmentStart::Segment_ID) << endl;
      return;
   }
}

void IsuCompetition::AddSegment(OsisSegment* newSegment)
{
   int SID = newSegment->GetId();
   if (SID == -1)
   {
      return;
   }
   if (Current_Category == -1)
   {
      qCritical() << "Undefined Category when processing Segment ID: " << newSegment->GetAttribute(OsisSegment::ID) << endl;
      return;
   }

   newSegment->SetCategoryId(Current_Category);

   if (Segments.contains(SID))
   {
      Segments.value(SID)->Update(*newSegment);
      delete newSegment;
   }
   else
   {
      Segments[SID] = newSegment;
   }

   if (Categories.contains(Current_Category))
   {
      Categories[Current_Category]->AddSegment(Segments[SID]);
   }
}

void IsuCompetition::AddParticipant(OsisParticipant* newParticipant)
{
   int PID = newParticipant->GetId();
   if (PID == -1)
   {
      Current_Participant = 0;
      return;
   }

   if (Participants.contains(PID))
   {
      Participants.value(PID)->Update(*newParticipant);
      delete newParticipant;
   }
   else
   {
      Participants[PID] = newParticipant;
   }

   if  (Categories.contains(Current_Category))
   {
      Categories[Current_Category]->AddParticipant(Participants[PID]);
   }
   Current_Participant = Participants[PID];
}

void IsuCompetition::AddCriteria(OsisCriteria* newCriteria)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing a Criteria : " << newCriteria->GetAttribute(OsisCriteria::Index) << " :" << newCriteria->GetAttribute(OsisCriteria::Cri_Name) << endl;
      return;
   }

   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddCriteria(newCriteria);
   }
}

void IsuCompetition::AddDeduction(OsisDeduction* newDeduction)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing a Deduction : " << newDeduction->GetAttribute(OsisDeduction::Index) << " :" << newDeduction->GetAttribute(OsisDeduction::Ded_Name) << endl;
      return;
   }
   int index = newDeduction->GetIndex();
   if (index == -1)
   {
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddDeduction(newDeduction);
   }
}

void IsuCompetition::AddMajorityDeduction(OsisMajorityDeduction* newMajorityDeduction)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing a MajorityDeduction : " << newMajorityDeduction->GetAttribute(OsisMajorityDeduction::Index) << endl;
      return;
   }

   int index = newMajorityDeduction->GetIndex();
   if (index == -1)
   {
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddMajorityDeduction(newMajorityDeduction);
   }
}

void IsuCompetition::AddOfficial(OsisOfficial* newOfficial)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing an Official: " << newOfficial->GetAttribute(OsisOfficial::Index) << " Full_Name=" << newOfficial->GetAttribute(OsisOfficial::Full_Name) <<endl;
      return;
   }
   int index = newOfficial->GetIndex();
   if (index == -1)
   {
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddOfficial(newOfficial);
   }
}

void IsuCompetition::AddAthlete(OsisAthlete* newAthlete)
{
   if (!Current_Participant)
   {
      qCritical() << "Cannot process Athlete: Missing Participant info" << endl;
      return;
   }
   Current_Participant->AddAthlete(newAthlete);
}

void IsuCompetition::AddPerformance(OsisPerformance* newPerformance)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing Performance: " << newPerformance->GetAttribute(OsisPerformance::ID) << endl;
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddPerformance(newPerformance);
   }
}

void IsuCompetition::AddElement(OsisElement* newElement)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing Element: " << newElement->GetAttribute(OsisElement::Index) << endl;
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddElement(newElement);
   }
}

void IsuCompetition::AddWarmupGroup(OsisWarmupGroup* newWarmupGroup)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing Warmup_Group: " << newWarmupGroup->GetAttribute(OsisWarmupGroup::Index) << endl;
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddWarmupGroup(newWarmupGroup);
   }
}

void IsuCompetition::AddPrfRanking(OsisPrfRanking* newPrfRanking)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing Prf_Ranking: " << newPrfRanking->GetAttribute(OsisPrfRanking::TypeName) << endl;
      return;
   }
   if (Segments.contains(Current_Segment))
   {
      Segments[Current_Segment]->AddPrfRanking(newPrfRanking);
   }
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
      Current_Segment = SegId;
   }
   else
   {
      Current_Segment = -1;
   }
}

void IsuCompetition::ProcessAction(OsisAction* newAction)
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
}
