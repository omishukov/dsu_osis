/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISXML_H
#define OSISXML_H

#include <QDomDocument>
#include <QObject>
#include "event.h"

class OsisXml: public QObject
{
   Q_OBJECT
public:
   enum OsisElements
   {
      ISU_OSIS,
      // <Event_Overview>
      Event_Overview,
      Event,
      Category_List,
      Category,
      // <Segment_Start>
      Segment_Start,
      Event_Officials_List,
      Official,
      Participant_List,
      Category_Result_List,
      Segment_List,
      Participant,
      Coaches, // always empty
      Athlete_List,
      Segment,
      Criteria_List,
      Deduction_List,
      Majority_Deduction_List,
      Segment_Official_List,
      Segment_Start_List,
      Athlete,
      Criteria,
      Deduction,
      Majority_Deduction,
      Performance,
      Planned_Element_List,
      Element,
      // <Segment_Running>
      Segment_Running,
      Action,
      Prf_Details,
      Prf_Ranking,
      Segment_Result_List,
      Element_List,
      Prf,
      // <Segment_Statistic>
      Segment_Statistic,
   };
   Q_ENUM(OsisElements)

public:
   explicit OsisXml(QObject *parent = 0);

   void ProcessOsisData(QDomNode& n);
   bool ProcessOsisTree(QDomNode& n);
   bool ProcessOsisElement(QDomNode& n);

   OsisEvent event;
};

#endif // OSISXML_H
