#ifndef OSISACTION_H
#define OSISACTION_H

#include <QObject>
#include <QDomDocument>
#include <osisdata.h>

class OsisAction : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisAction(QDomElement& osisElement, QObject *parent = 0);

public:
   enum OsisElementAttributes
   {
      Command, // 3, See action codes
      Current_Participant_ID, // ID of current participant
      Current_Start_Number, // Starting number of current participant
      Next_Participant_ID, // Next active participant. Empty, if current participant is last in segment
      Prev_Participant_ID, // Previous participant. Empty, if current participant is first in segment
      Next_Participant_StNum, // Starting Number of the next active participant. Empty, if current participant is last in segment
      LastScored_Participant_StNum, // Starting Number of the last scored participant. Empty, if no scored participant is available in segment
      Sub_Command, // Sub command of action
      Clock_State, // See clock status code
      Running_Time
   };

   enum OsisActionCodes
   {
      AC_1SC, // Send Technical Element score Note: A message with 1SC action code is sent after the calculation of a performance result.
           // Due to the big size of the message, it was split into several messages.
           // Instead of one message with 1SC action code a sequence of 6 messages is sent in the following order: 1S1, 1S2, 1S3, 1S4, (1S5,) 1SC.
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

   Q_ENUM(OsisElementAttributes)
   Q_ENUM(OsisActionCodes)
};

#endif // OSISACTION_H
