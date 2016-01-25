#ifndef ISUCOMPETITION_H
#define ISUCOMPETITION_H

#include "osis/osisxml.h"
#include "osis/competitionif.h"
#include "osis/event.h"
#include "osis/category.h"
#include "osis/segmentstart.h"
#include "osis/participant.h"
#include "osis/segment.h"
#include "osis/criteria.h"
#include "osis/deduction.h"

class IsuCompetition: public OsisCompetitionIf
{
public:
   IsuCompetition();
   ~IsuCompetition();

   OsisDataIf* GetDataIf() { return osisInfo; }

   void AddEvent(OsisEvent *newEvent);
   void AddCategory(OsisCategory *newCategory);
   void AddSegmentStart(OsisSegmentStart* newSegmentStart);
   void AddParticipant(OsisParticipant* newParticipant);
   void AddSegment(OsisSegment* newSegment);
   void AddCriteria(OsisCriteria* newCriteria);
   void AddDeduction(OsisDeduction* newDeduction);

   void ProcessingDone() {}

private:
   OsisXml *osisInfo;
   OsisEvent* Event;
   int Current_Category;
   OsisCategoryMap Categories;
   OsisSegmentStart *Segment_Start;
   int Current_Segment;
   OsisParticipantMap Participants;
   OsisSegmentMap Segments;
   OsisCriteriaMap Criteries;

};

#endif // ISUCOMPETITION_H
