/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef ISUCOMPETITION_H
#define ISUCOMPETITION_H

#include "osis/osisxml.h"
#include "osis/competitionif.h"
#include "element/category.h"
#include "element/segmentstart.h"
#include "element/participant.h"
#include "element/segment.h"
#include "element/criteria.h"
#include "element/deduction.h"
#include "element/majoritydeduction.h"
#include "element/official.h"
#include "element/athlete.h"
#include "element/performance.h"
#include "element/element.h"
#include "element/warmupgroup.h"
#include "element/prfranking.h"
#include "element/segmentrunning.h"
#include "element/action.h"
#include "element/prfdetails.h"
#include "element/event.h"
#include "element/isuosis.h"
#include "obs/actions.h"

class IsuCompetition: public OsisCompetitionIf
{
public:
   IsuCompetition(Actions* actions);
   ~IsuCompetition();

   OsisDataIf* GetDataIf() { return osisInfo; }

   void AddIsuOsis(IsuOsis *newIsuOsis);
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
   void AddSegmentRunning(OsisSegmentRunning* newSegmentRunning);
   void AddAction(OsisAction* newAction);
   void AddPrfDetails(OsisPrfDetails* newPrfDetails);
   void AddElementList(OsisElementList* newElementList);

   void ProcessAction(int action);
   void ProcessingDone();

   void Uninit();

private:
   int Current_DB_ID;
   OsisEvent* Current_Event;
   int Last_Category_Id; // Used to process Category and Segment XML elements
   int Last_Participant_Id;

private:
   OsisXml *osisInfo;
   int Current_Category_Id;

   OsisCategoryMap Categories;

   OsisSegmentStart *Segment_Start;
   int Current_Segment_Id;
   OsisParticipantMap Participants;
   OsisSegmentMap Segments;
   OsisOfficialMap Officials;
   OsisParticipant* Current_Participant;
   OsisAction* Current_Action;
   Actions* actionHandler;

   OsisCriteriaMap Criteries;
};

#endif // ISUCOMPETITION_H
