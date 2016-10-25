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
      Running_Time,
      Judge_ID
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisAction(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int Current_Participant_Id;
};

#endif // OSISACTION_H
