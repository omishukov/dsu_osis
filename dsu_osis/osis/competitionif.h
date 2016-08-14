#ifndef COMPETITIONIF_H
#define COMPETITIONIF_H

class OsisCompetitionIf
{
public:
   virtual ~OsisCompetitionIf() {}

   virtual void AddIsuOsis(class IsuOsis *newIsuOsis) = 0;
   virtual void AddEvent(class OsisEvent* newEvent) = 0;
   virtual void AddCategory(class OsisCategory* newCategory) = 0;
   virtual void AddSegmentStart(class OsisSegmentStart* newSegmentStart) = 0;
   virtual void AddParticipant(class OsisParticipant* newParticipant) = 0;
   virtual void AddSegment(class OsisSegment* newSegment) = 0;
   virtual void AddCriteria(class OsisCriteria* newCriteria) = 0;
   virtual void AddDeduction(class OsisDeduction* newDeduction) = 0;
   virtual void AddMajorityDeduction(class OsisMajorityDeduction* newDeduction) = 0;
   virtual void AddOfficial(class OsisOfficial* newOfficial) = 0;
   virtual void AddAthlete(class OsisAthlete* newAthlete) = 0;
   virtual void AddPerformance(class OsisPerformance* newPerformance) = 0;
   virtual void AddElement(class OsisElement* newElement) = 0;
   virtual void AddWarmupGroup(class OsisWarmupGroup* newWarmupGroup) = 0;
   virtual void AddPrfRanking(class OsisPrfRanking* newPrfRanking) = 0;
   virtual void AddSegmentRunning(class OsisSegmentRunning* newSegmentRunning) = 0;
   virtual void AddAction(class OsisAction* newAction) = 0;
   virtual void AddPrfDetails(class OsisPrfDetails* newPrfDetails) = 0;
   virtual void AddElementList(class OsisElementList* newElementList) = 0;

   virtual void ProcessAction(int action) = 0;

   virtual void ProcessingDone() = 0;

   virtual void Uninit() = 0;
};

#endif // COMPETITIONIF_H

