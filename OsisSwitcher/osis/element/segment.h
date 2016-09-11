/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISSEGMENT_H
#define OSISSEGMENT_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

/*
 * <Segment ID="2" Name="Free Skating" Abbreviation="FS" Date="20151003" Start="09:05:00" Status="g" End="00:00:00" ExtDt=""/>
 * <Segment ID="17" Name="Short Program" Abbreviation="SP" Name_Of_Dance="" Type="S" Number_Of_Judges="3" Number_Of_Decisive_Judges="3" Group="" QCrit="A" QNumber="0" ExtDt="" Medal="0">
 */

class OsisSegment : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      ID, // Identifier
      Name, // 40
      Abbreviation, // 3
      Name_Of_Dance, // 30
      Type, // See segment type code
      Number_Of_Judges, //
      Number_Of_Decisive_Judges, //
      QCrit, // Qualifying Criteria
      QNumber, // Number of participants to be
      Date, //
      Start, // Start time
      Status, // See segment status code
      End, // End time
      ExtDt, // 10 RSC Code
      Medal, // 1 Is medal segment flag
      qualified, //
      Group
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisSegment(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int Id;
   int CategoryId;
};

typedef QMap <int, OsisSegment*> OsisSegmentMap;

#endif // OSISSEGMENT_H
