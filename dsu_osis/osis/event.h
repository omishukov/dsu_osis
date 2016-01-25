/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

class OsisEvent: public QObject, public OsisData
{
   Q_OBJECT

public:
   OsisEvent(QDomElement& eventElement, QObject *parent = 0);
   ~OsisEvent();

public:
   enum OsisElementAttributes
   {
      ID, // Identifier
      Name, //
      Abbreviation, //
      Type, // Type of the event, standard value: “T”
      CmpType, // Competition type
      ExtDt, // Results System Codes
      ODF // ???
   };
   Q_ENUM(OsisElementAttributes)

public:
   bool ProcessDeduction(QDomElement& deductionElement);
   bool ProcessCriteriaList(QDomElement& criteriaListElement, int SegmentId);
   bool ProcessOfficial(QDomElement& officialElement);
   bool ProcessAthlete(QDomElement& athleteElement);


   void ProcessingDone();

private:
   int event_ID;
   QString event_Name;
   QString event_Abbreviation;
   QString event_Type;
   QString event_CmpType;
   QString event_ExtDt;
   int event_ODF;

   int Current_Category;
   int Current_Segment;
};

#endif // EVENT_H
