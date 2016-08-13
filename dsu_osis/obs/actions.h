#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <QList>
#include <QMetaEnum>
#include <obsosisif.h>

class Actions : public QObject
{
   Q_OBJECT
public:
   enum ObsAction
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
      ACTION_WUP,  // send warm up group

      EVENT_OVERVIEW, // <Event_Overview>: Create
                     // * Todays competition schedule
                     // * Competition Name
      SEGMENT_START, // <Segment_Start>: Basing on Segment_ID create sorted list of
                         // * Current Category Name
                         // * Current Segment Name
                         // * Participants
                         // * Warmup groups
                         // * Officials
      PRF_RANKING, // <Prf_Ranking>
      SEGMENT_RESULT_LIST,
      CATEGORY_RESULT_LIST
   };
   Q_ENUM(ObsAction)

public:
   Actions();

   void DoActions();
   void AddAction(int action);

   void SetOsisInfoIf(ObsOsisIf* obsOsisIf) { OsisIf = obsOsisIf; }

private:
   void SaveToFile(const QString& file, const QString& text);
   void GenerateHtml(QMap<int, QList<QString>>& segmentStartList);

private:
   QList<int> ActionList;
   QMetaEnum MetaActionsEnum;
   ObsOsisIf* OsisIf;
};

#endif // ACTIONS_H
