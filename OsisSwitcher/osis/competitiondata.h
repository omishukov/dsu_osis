#ifndef OSISCOMPETITIONDATA_H
#define OSISCOMPETITIONDATA_H

#include <QObject>
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
#include "element/elementlist.h"
#include "element/warmupgroup.h"
#include "element/prfranking.h"
#include "element/segmentrunning.h"
#include "element/action.h"
#include "element/prfdetails.h"
#include "element/event.h"
#include "element/isuosis.h"
#include "obsosisif.h"

class OsisCompetitionData : public QObject, public ObsOsisIf
{
   Q_OBJECT
public:
   explicit OsisCompetitionData(QObject *parent = 0);
   ~OsisCompetitionData();

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

   QString GetCurrentSkaterName();
   QString GetCurrentSkaterNumber();
   QString GetCurrentSkaterNation();
   QString GetCurrentSkaterClub();
   QString GetEventName();
   QString GetEventAbbreviation();
   QString GetSegmentName();
   QString GetCategoryName();
   bool GetSegmentStartList(QMap<int, QList<QString> >& segmentStartList);
   bool GetWarmUpStartList(QMap<int, QList<QString>>& warmUpStartList);
   bool GetSegmentResultList(QMap<int, QList<QString> >& segmentResultList);
   bool GetCategoryResultList(QMap<int, QList<QString> >& categoryResultList);
   void GetWarmUpGroupsList(QList<int>& WarmUpList);
   QString GetPoints();
   QString GetTPoints();
   QString GetTES();
   QString GetTCS();
   QString GetBonus();
   QString GetDeduction();
   QString GetRank();
   QString GetTRank();
   QString GetCurrentWarmUpGroupNumber();

signals:
   void NewAction(int);
   void DoActions();

public slots:

private:
   int CurrentStartNumber();

   int Current_DB_ID;
   OsisEvent* Current_Event;
   int Current_Category_Id;
   int Current_Segment_Id;
   int Last_Category_Id;
   OsisCategoryMap Categories;
   OsisSegmentMap Segments;
   int Last_Participant_Id;
   OsisParticipantMap Participants;
   OsisPerformanceMap Performances;
   OsisWarmupGroupMap WarmupGroups;
   OsisAction* Current_Action;
   OsisPrfDetails* Current_Performance_Result;
   int CurrentParticipantId;
};

#endif // OSISCOMPETITIONDATA_H
