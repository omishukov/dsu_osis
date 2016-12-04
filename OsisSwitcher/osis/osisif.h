#ifndef OBSOSISIF_H
#define OBSOSISIF_H

#include <QObject>
#include <QString>
#include <QMap>

class OsisIf : public QObject
{
   Q_OBJECT
public:
   explicit OsisIf(QObject *parent = 0) : QObject(parent) {}
   virtual ~OsisIf() {}

   virtual const QMap<int, QString>* GetActions() const = 0;
   virtual QString GetActionName(int action) = 0;

   virtual QString GetCurrentSkaterName() = 0;
   virtual QString GetCurrentSkaterNumber() = 0;
   virtual QString GetCurrentSkaterNation() = 0;
   virtual QString GetCurrentSkaterClub() = 0;
   virtual QString GetEventName() = 0;
   virtual QString GetEventAbbreviation() = 0;
   virtual QString GetSegmentName() = 0;
   virtual QString GetCategoryName() = 0;
   virtual QString GetPoints() = 0;
   virtual QString GetTES() = 0;
   virtual QString GetTCS() = 0;
   virtual QString GetBonus() = 0;
   virtual QString GetDeduction() = 0;
   virtual QString GetRank() = 0;
   virtual QString GetCurrentWarmUpGroupNumber() = 0;
   virtual bool GetSegmentStartList(QMap<int, QList<QString>>& segmentStartList) = 0;
   virtual bool GetSegmentResultList(QMap<int, QList<QString>>& segmentResultList) = 0;
   virtual bool GetWarmUpStartList(QMap<int, QList<QString>>& warmUpStartList) = 0;
   virtual void GetWarmUpGroupsList(QList<int>& WarmUpList) = 0;

   enum OSIS_ACTIONS_ENUM
   {
      NO_ACTIONS,
      ACTION_1SC, // Send Technical Element score Note: A message with 1SC action code is sent after the calculation of a performance result.
                  // Due to the big size of the message, it was split into several messages.
                  // Instead of one message with 1SC action code a sequence of 6 messages is sent in the following order: 1S1, 1S2, 1S3, 1S4, (1S5,) 1SC.
      ACTION_1S1, // Result of current performance
      ACTION_1S2, // Segment ranking
      ACTION_1S3, // Category standing
      ACTION_1S4, // Remaining start list
      ACTION_1S5, // Team Standing
      ACTION_2SC, // Send Program Components score
      ACTION_3SC, // Send total score
      ACTION_CLR, // Clear scoreboard
      ACTION_ELM, // Executed elements of current performer
      ACTION_ELS, // Live calculation of current Skater
      ACTION_INI, // Initialise
      ACTION_IDT, // Send logo
      ACTION_IRS, // Send intermediate result
      ACTION_JDG, // Send judge
      ACTION_LTV, // Live Technical Element Score (TES)
      ACTION_NAM, // send name of active performer
      ACTION_NXP, // send next page (result or start list page)
      ACTION_RES, // Send result
      ACTION_SEG, // Send segment name
      ACTION_STL, // Send start list
      ACTION_STP, // Stop
      ACTION_NXT, // Next performer
      ACTION_PRV, // Previous performer
      ACTION_TBW, // Time count backward
      ACTION_TFW, // Time count forward
      ACTION_TR1, // Overall team standing
      ACTION_TR2, // Overall team standing
      ACTION_TST, // Time stopped
      ACTION_TPA, // Time pause
      ACTION_TCL, // Clear time
      ACTION_TIM, // Time value
      ACTION_URK, // Ranking Update
      ACTION_VTR, // Victory Ceremony
      ACTION_WUP, // send warm up group

      LAST_ACTION
   };
   Q_ENUM(OSIS_ACTIONS_ENUM)

};

#endif // OBSOSISIF_H

