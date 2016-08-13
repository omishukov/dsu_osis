/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISOFFICIAL_H
#define OSISOFFICIAL_H

#include <QObject>
#include <QMap>
#include "osisdata.h"

/*
 * <Official Index="1" ID="212" Full_Name="Mr. Jesper HOLKJÆR" Title="Mr." Family_Name="HOLKJÆR" Given_Name="Jesper" Initial="J." ScbName1="Jesper HOLKJÆR" ScbName4="Jesper HOLKJÆR" Gender="M" Nation="DEN" Club="" Function="JDG"/>
 */

class OsisOfficial : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Index, //connected to the function
      ID, //Identifier,
      Full_Name,
      Title,
      Family_Name,
      Given_Name,
      Initial, //Initial of the given name
      ScbName1, //Scoreboard name string
      Gender, // F | M
      Nation,
      Club,
      Function //OsisOfficialFunctionAttribute
   };

   QString OsisOfficialFunctionAttribute[10]
   {
      "JDG", //Judge
      "ERF", //Referee
      "TCO", //Technical controller
      "TSP", //Technical specialist
      "STS", //Assistant technical specialist
      "ARI", //Assistant referee ice
      "DOP", //Data operator
      "ROP", //Replay operator
      "REP", //ISU representative
      "TDG", //Technical delegate
   };

   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisOfficial(QDomElement& categoryElement, QString& elementName, QObject *parent = 0);

   int Ind;
};

typedef QMap <int, OsisOfficial*> OsisOfficialMap;

#endif // OSISOFFICIAL_H
