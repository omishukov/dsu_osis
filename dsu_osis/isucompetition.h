/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

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
#include "osis/majoritydeduction.h"
#include "osis/official.h"
#include "athlete.h"
#include "element/performance.h"
#include "element/element.h"
#include "element/warmupgroup.h"
#include "element/prfranking.h"

class IsuCompetition: public OsisCompetitionIf
{
public:
   IsuCompetition();
   ~IsuCompetition();

   OsisDataIf* GetDataIf() { return osisInfo; }

   void AddEvent(OsisEvent *newEvent);
   void AddCategory(OsisCategory *newCategory);
   void AddSegmentStart(OsisSegmentStart* newSegmentStart);
   void AddSegment(OsisSegment* newSegment);
   void AddParticipant(OsisParticipant* newParticipant);
   void AddCriteria(OsisCriteria* newCriteria);
   void AddDeduction(OsisDeduction* newDeduction);
   void AddMajorityDeduction(OsisMajorityDeduction* newMajorityDeduction);
   void AddOfficial(OsisOfficial* newOfficial);
   void AddAthlete(OsisAthlete* newAthlete);
   void AddPerformance(OsisPerformance* newPerformance);
   void AddElement(OsisElement* newElement);
   void AddWarmupGroup(OsisWarmupGroup* newWarmupGroup);
   void AddPrfRanking(OsisPrfRanking* newPrfRanking);

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
   OsisOfficialMap Officials;
   OsisParticipant* Current_Participant;
};

#endif // ISUCOMPETITION_H
