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
};

#endif // OSISACTION_H
