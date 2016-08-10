/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISACTION_H
#define OSISACTION_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Action Command="INI" Current_Participant_ID="8" Current_Start_Number="1" Next_Participant_ID="94" Prev_Participant_ID="" Next_Participant_StNum="2" LastScored_Participant_StNum="0"/>
 */

class OsisAction : public QObject, public OsisData
{
   Q_OBJECT
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
   Q_ENUM(OsisElementAttributes)

   QString OsisActionCodes[35]
   {
      "1SC", // Send Technical Element score Note: A message with 1SC action code is sent after the calculation of a performance result.
             // Due to the big size of the message, it was split into several messages.
             // Instead of one message with 1SC action code a sequence of 6 messages is sent in the following order: 1S1, 1S2, 1S3, 1S4, (1S5,) 1SC.
      "1S1", // Result of current performance
      "1S2", // Segment ranking
      "1S3", // Category standing
      "1S4", // Remaining start list
      "1S5", // Team Standing
      "2SC", // Send Program Components score
      "3SC", // Send total score
      "CLR", // Clear scoreboard
      "ELM", // Executed elements of current performer
      "ELS", // Live calculation of current Skater
      "INI", // Initialise
      "IDT", // Send logo
      "IRS", // Send intermediate result
      "JDG", // Send judge
      "LTV", // Live Technical Element Score (TES)
      "NAM", // send name of active performer
      "NXP", // send next page (result or start list page)
      "RES", // Send result
      "SEG", // Send segment name
      "STL", // Send start list
      "STP", // Stop
      "NXT", // Next performer
      "PRV", // Previous performer
      "TBW", // Time count backward
      "TFW", // Time count forward
      "TR1", // Overall team standing
      "TR2", // Overall team standing
      "TST", // Time stopped
      "TPA", // Time pause
      "TCL", // Clear time
      "TIM", // Time value
      "URK", // Ranking Update
      "VTR", // Victory Ceremony
      "WUP"  // send warm up group
   };

public:
   explicit OsisAction(QDomElement& osisElement, const char* elementName, QObject *parent = 0);

   int Current_Participant_Id;
};

#endif // OSISACTION_H
