/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISPARTICIPANT_H
#define OSISPARTICIPANT_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

class OsisParticipant : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisParticipant(QObject *parent = 0);

   enum OsisElementAttributes
   {
      ID, // Identifier
      Status, // See OsisParticipantStatus
      Type, // See participant type code
      Full_Name, // 60
      Short_Name, // 30
      TV_Long_Name, // 40
      TV_Short_Name, // 30
      ScbName1, // 30 ScoreboardName1
      ScbName2, // 30 ScoreboardName2
      ScbName3, // 30 ScoreboardName3
      ScbName4, // 30 ScoreboardName4
      Nation, // 3
      Music, // 40 Music description
      Coach, // 40 Coach Names
      Club, // 11 Max length: singles = 5, couples = 11
      ExtRef, // 10 Reference ID to external database
      RegNum, // 16 ORIS registration number
      TeamName, // -
      TeamNation, // -
      Index, //
      TIndex, // Total display position
      TRank, // Total rank
      TPoint, // Total points, format: “0.00”
      Segment1_Status, // 40 Status of participant
      Segment2_Status,
      Segment3_Status,
      Segment4_Status,
      Segment5_Status,
      Segment6_Status,
      Segment1_Rank, // 30 Rank of participant segment
      Segment2_Rank,
      Segment3_Rank,
      Segment4_Rank,
      Segment5_Rank,
      Segment6_Rank,
      Segment1_Index, // 30 {n} = 1...6; Displaypos of participant
      Segment2_Index,
      Segment3_Index,
      Segment4_Index,
      Segment5_Index,
      Segment6_Index,
      Segment1_Points, // 30 {n} = 1...6; Points of participant segment
      Segment2_Points,
      Segment3_Points,
      Segment4_Points,
      Segment5_Points,
      Segment6_Points,
      Segment1_IIndex, // 30 {n} = 1...6; Displaypos of participant in the (n-1)-th
      Segment2_IIndex,
      Segment3_IIndex,
      Segment4_IIndex,
      Segment5_IIndex,
      Segment6_IIndex,
      Segment1_IRank, // 30 {n} = 1...6; Rank of participant in the (n-1)-th
      Segment2_IRank,
      Segment3_IRank,
      Segment4_IRank,
      Segment5_IRank,
      Segment6_IRank,
   };

   enum OsisParticipantStatus
   {
      ACT, // Active
      WDR, // Withdrawn
      EWD, // Entry withdrawn
      NQD, // Not qualified
      FNR, // Final not reached
      DSQ, // Disqualified
      SEN, // Substitute entry
   };

   enum OsisParticipantType
   {
      PER, // Person
      COU, // Couple
      PTS, // Team
      MIX,
      Type_MAX
   };

   enum OsisPerformanceStatus
   {
      L, // Remaining
      M, // Not in segment
      O, // Ok
      I, // Invalid result
      PerfStatus_MAX
   };

   Q_ENUM(OsisElementAttributes)
   Q_ENUM(OsisParticipantStatus)
   Q_ENUM(OsisParticipantType)
   Q_ENUM(OsisPerformanceStatus)

signals:

public slots:

private:
};

#endif // OSISPARTICIPANT_H
