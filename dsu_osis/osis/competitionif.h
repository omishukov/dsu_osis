#ifndef COMPETITIONIF_H
#define COMPETITIONIF_H

class OsisCompetitionIf
{
public:
   virtual ~OsisCompetitionIf() {}

   virtual void AddEvent(class OsisEvent* newEvent) = 0;
   virtual void AddCategory(class OsisCategory* newCategory) = 0;
   virtual void AddSegmentStart(class OsisSegmentStart* newSegmentStart) = 0;
   virtual void AddParticipant(class OsisParticipant* newParticipant) = 0;
   virtual void AddSegment(class OsisSegment* newSegment) = 0;
   virtual void AddCriteria(class OsisCriteria* newCriteria) = 0;
   virtual void AddDeduction(class OsisDeduction* newDeduction) = 0;

   virtual void ProcessingDone() = 0;
};

#endif // COMPETITIONIF_H

