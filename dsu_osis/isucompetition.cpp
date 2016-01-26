#include <QDebug>
#include "isucompetition.h"

IsuCompetition::IsuCompetition()
   : osisInfo(new OsisXml(this))
   , Event(0)
   , Current_Category(-1)
   , Segment_Start(0)
   , Current_Segment(-1)
{

}

IsuCompetition::~IsuCompetition()
{
   delete Event;

}

void IsuCompetition::AddEvent(OsisEvent* newEvent)
{
   Event = newEvent;
   foreach (OsisCategory* category, Categories)
   {
      delete category;
   }
   delete Segment_Start;
   foreach (OsisParticipant* participant, Participants)
   {
      delete participant;
   }
   foreach (OsisSegment* segment, Segments)
   {
      delete segment;
   }
   foreach (OsisCriteria* criteria, Criteries)
   {
      delete criteria;
   }
}

void IsuCompetition::AddCategory(OsisCategory* newCategory)
{
   bool ok;
   Current_Category = newCategory->GetAttribute(OsisCategory::ID).toInt(&ok);
   if (!ok)
   {
      qCritical() << "Invalid category: " << newCategory->GetAttribute(OsisCategory::ID) << endl;
      return; // Report Warning: Invalid Category
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

void IsuCompetition::AddParticipant(OsisParticipant* newParticipant)
{
   bool ok;
   int PID = newParticipant->GetAttribute(OsisParticipant::ID).toInt(&ok);
   if (!ok)
   {
      qCritical() << "Wrong Participant ID: " << newParticipant->GetAttribute(OsisParticipant::ID) << endl;
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
}

void IsuCompetition::AddSegment(OsisSegment* newSegment)
{
   bool ok;
   int SID = newSegment->GetAttribute(OsisSegment::ID).toInt(&ok);
   if (!ok)
   {
      qCritical() << "Wrong Segment ID: " << newSegment->GetAttribute(OsisSegment::ID) << endl;
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
}

void IsuCompetition::AddCriteria(OsisCriteria* newCriteria)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing a Criteria : " << newCriteria->GetAttribute(OsisCriteria::Index) << " :" << newCriteria->GetAttribute(OsisCriteria::Cri_Name) << endl;
      return;
   }
   newCriteria->SetSegmentId(Current_Segment);

   bool ok;
   int index = newCriteria->GetAttribute(OsisCriteria::Index).toInt(&ok);
   if (!ok)
   {
      qCritical() << "Wrong Criteria Index: " << newCriteria->GetAttribute(OsisCriteria::Index) << " in Segment ID: " << Current_Segment << endl;
      return;
   }
   bool found = false;
   foreach (OsisCriteria* criteria, Criteries)
   {
      if (criteria->GetSegmentId() == Current_Segment)
      {
         if (criteria->GetAttribute(OsisCriteria::Index).toInt(&ok) == index && ok)
         {
            criteria->Update(*newCriteria);
            found = true;
            delete newCriteria;
            break;
         }
      }
   }
   if (!found)
   {
      Criteries.insert(Current_Segment, newCriteria);
   }
}

void IsuCompetition::AddDeduction(OsisDeduction* newDeduction)
{
   if (Current_Segment == -1)
   {
      qCritical() << "Undefined Segment ID when processing a Deduction : " << newDeduction->GetAttribute(OsisDeduction::Index) << " :" << newDeduction->GetAttribute(OsisDeduction::Ded_Name) << endl;
      return;
   }
   newDeduction->SetSegmentId(Current_Segment);

   bool ok;
   int index = newDeduction->GetAttribute(OsisCriteria::Index).toInt(&ok);
   if (!ok)
   {
      qCritical() << "Wrong Deduction Index: " << newDeduction->GetAttribute(OsisDeduction::Index) << " in Segment ID: " << Current_Segment << endl;
      return;
   }
   bool found = false;
   foreach (OsisDeduction* deduction, Deductions)
   {
      if (deduction->GetSegmentId() == Current_Segment)
      {
         if (deduction->GetAttribute(OsisDeduction::Index).toInt(&ok) == index && ok)
         {
            deduction->Update(*newDeduction);
            found = true;
            delete newDeduction;
            break;
         }
      }
   }
   if (!found)
   {
      Deductions.insert(Current_Segment, newDeduction);
   }
}
