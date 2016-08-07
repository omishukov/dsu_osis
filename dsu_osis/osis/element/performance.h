/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISPERFORMANCE_H
#define OSISPERFORMANCE_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

/*
 * <Performance ID="8" Start_Number="1" Start_Group_Number="1" PElmScore="6.30" Personal_Best="0.00" Personal_Best_Tot="0.00" Status="REM" Season_Best="0.00" Season_Best_Tot="0.00" Season_Best_Rank="0" Season_Best_Index="11" Season_Best_Tot_Rank="0" Season_Best_Tot_Index="11" StartTime="" Prf_ID="69">
 * <Performance ID="8" Start_Number="1" Points_Needed1="0.00" Points_Needed2="0.00" Points_Needed3="0.00" Status="REM"/>
 */

class OsisPerformance : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      ID, // Identifier
      Start_Number,
      Start_Group_Number,
      PElmScore, //Planned element score
      Personal_Best, //Personal best in segment
      Personal_Best_Tot, //Total personal best
      Season_Best, //Season best in segment
      Season_Best_Tot, //Total season best
      Season_Best_Rank,
      Season_Best_Index,
      Season_Best_Tot_Rank,
      Season_Best_Tot_Index,
      Status, //Performance status
      Points, //Format “9.99”
      TES, //Technical element score
      TCS, //Program component score
      Bonus,
      Ded_Sum, //Sum of the deductions, Format “9.99”
      Qualified, //“Q” when qualified
      Points_Needed1, //Required points to get into 1st position
      Points_Needed2, //Required points to get into 2nd position
      Points_Needed3, //Required points to get into 3rd position
      StartTime,
      Prf_ID
   };
   Q_ENUM(OsisElementAttributes)

   QString OsisPerformanceStatus[4]
   {
      "REM", //Remaining
      "OK", //Ok, skater received result, which is valid for ranking
      "IRM", //Invalid result mark (withdrawn, disqualified)
      "NIS" //Not in segment
   };

public:
   explicit OsisPerformance(QDomElement& categoryElement, const char* elementName, QObject *parent = 0);

   int Id;
};

typedef QMap <int, OsisPerformance*> OsisPerformanceMap;

#endif // OSISPERFORMANCE_H
