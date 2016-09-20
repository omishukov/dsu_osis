/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISATHLETE_H
#define OSISATHLETE_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

/*
 * <Athlete ID="96" Type="PER" Nation="TSK" Full_Name="Katrine HANSEN" Initial_Name="HANSEN, K." Family_Name="HANSEN" Given_Name="Katrine" Printed_Long_Name="Katrine HANSEN" Printed_Short_Name="Katrine HANSEN" Initial="K." ScbName1="Katrine HANSEN" ScbName2="Katrine HANSEN" ScbName3="Katrine HANSEN" ScbName4="Katrine HANSEN" TV_Long_Name="Katrine HANSEN" TV_Short_Name="Katrine HANSEN" RTDS_Long_Name="" RTDS_Short_Name="" Gender="F" Date_Of_Birth="2002-06-11" ExtRef="" RegNum="" Organisation=""/>
 */

class OsisAthlete : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      ID, //  Identifier
      Index,
      Type,
      Nation,
      Full_Name, // 60
      Initial_Name, // 40 Format “Smith, D”
      Family_Name, // 30
      Given_Name, // 30
      ScbName1, // 30
      ScoreboardName1,
      ScbName2, // 30
      ScoreboardName2,
      ScbName3, // 30
      ScoreboardName3,
      ScbName4, // 30
      ScoreboardName4,
      TV_Long_Name, // 40
      TV_Short_Name, // 30
      RTDS_Long_Name, // 60
      RTDS_Short_Name, // 30
      Initial, //  Initial of given name
      Gender, // 1 M | F
      Date_Of_Birth, // 10 Format “YYYY-MM-DD”
      ExtRef, // 10  Reference ID to external database
      RegNum,
      Printed_Long_Name,
      Printed_Short_Name,
      Organisation
   };
   Q_ENUM(OsisElementAttributes)

   QString OsisAthleteType[4]
   {
      "PER", // Person
      "COU", // Couple
      "PTS", // Team
      "MIX"
   };


public:
   explicit OsisAthlete(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int Id;
};

typedef QMap <int, OsisAthlete*> OsisAthleteMap;

#endif // OSISATHLETE_H
