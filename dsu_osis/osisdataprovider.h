#ifndef OSISDATAPROVIDER_H
#define OSISDATAPROVIDER_H

#include <QObject>
#include <QByteArray>
#include <QDomDocument>
#include "osisdataif.h"
#include "osis/osisxml.h"

#if 0
// Action codes (AC) started with a number cannot be used in enums.
// Add a prefix to received AC string before using it in QMetaEnum.
const QString ActionCodePrefix = "AC_";
#endif

class OsisDataProvider: public QObject, public OsisDataIf
{
   Q_OBJECT
public:
   OsisDataProvider();
   ~OsisDataProvider();

public:
   virtual void DataInd(class QByteArray& qba);

public:

#if 0
char CategoryLevel[10][] =
{{"Adult", "ADU"},
{"Senior", "SEN"},
{"Junior", "JUN"},
{"Novice", "NOV"},
{"Pre-Novice", "PRE"},
{"Other", "OTH"},
{"Basic Novice", "NBS"},
{"Basic Novice A", "NBA"},
{"Basic Novice B", "NBB"},
{"Advanced Novice", "NAD"}};

   enum OsisEventOverviewEventCategoryListCategoryElements
   {
      Segment_List
   };

   enum OsisEventOverviewEventCategoryListCategorySegmentListElements
   {
      Segment
   };

   enum Osis_EventOverview_Event_CategoryList_Category_SegmentList_Segment_Attributes
   {
      S_ID, // Identifier
      S_Name, // 40
      S_Abbreviation, // 3
      S_Name_Of_Dance, // 30
      S_Type, // See segment type code
      S_Number_Of_Judges, //
      S_Number_Of_Decisive_Judges, //
      S_QCrit, // Qualifying Criteria
      S_QNumber, // Number of participants to be
      S_Date, //
      S_Start, // Start time
      S_Status, // See segment status code
      S_End, // End time
      S_ExtDt, // 10 RSC Code
      S_Medal, // 1 Is medal segment flag
      S_qualified
   };

   enum OsisSegmentRunningElements
   {
      Action,
      Prf_Details,
      Prf_Ranking,
      Segment_Result_List,
      Category_Result_List
   };

   enum OsisSegmentRunningActionAttributes
   {
      Command, // See action codes
      Current_Participant_ID, // ID of current participant
      Current_Start_Number, // Starting number of current participant
      Next_Participant_ID, // Next active participant
      Prev_Participant_ID, // Previous participant
      Next_Participant_StNum, // Starting Number of the next active
      LastScored_Participant_StNum, // Starting Number of the last scored
      Sub_Command, // Sub command of action
      Clock_State, // See clock status code (Depricated?)
      Program_time,
      Running_Time // !!!Not documented
   };

   enum OsisSegmentRunningAction
   {
      AC_1S1, // Result of current performance
      AC_1S2, // Segment ranking
      AC_1S3, // Category standing
      AC_1S4, // Remaining start list
      AC_1S5, // Team Standing
      AC_2SC, // Send Program Components score
      AC_3SC, // Send total score
      AC_CLR, // Clear scoreboard
      AC_ELM, // Executed elements of current performer
      AC_ELS, // Live calculation of current Skater
      AC_INI, // Initialise
      AC_IDT, // Send logo
      AC_IRS, // Send intermediate result
      AC_JDG, // Send judge
      AC_LTV, // Live Technical Element Score (TES)
      AC_NAM, // send name of active performer
      AC_NXP, // send next page (result or start list page)
      AC_RES, // Send result
      AC_SEG, // Send segment name
      AC_STL, // Send start list
      AC_STP, // Stop
      AC_NXT, // Next performer
      AC_PRV, // Previous performer
      AC_TBW, // Time count backward
      AC_TFW, // Time count forward
      AC_TR1, // Overall team standing
      AC_TR2, // Overall team standing
      AC_TST, // Time stopped
      AC_TPA, // Time pause
      AC_TCL, // Clear time
      AC_TIM, // Time value
      AC_URK, // Ranking Update
      AC_VTR, // Victory Ceremony
      AC_WUP  // send warm up group
   };
#endif

private:
   bool ProcessOsisData(QDomNode& n);
   bool ProcessOsisElement(QDomNode& n);

   OsisXml* osisMsg;
};

#endif // OSISDATAPROVIDER_H
