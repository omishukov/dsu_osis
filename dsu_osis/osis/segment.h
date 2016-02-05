/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISSEGMENT_H
#define OSISSEGMENT_H

#include <QObject>
#include "osisdata.h"
#include "criteria.h"
#include "deduction.h"
#include "majoritydeduction.h"
#include "official.h"
#include "element/performance.h"
#include "element/element.h"
#include "element/warmupgroup.h"
#include "element/prfranking.h"

class OsisSegment : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisSegment(QDomElement& osisElement, QObject *parent = 0);
   ~OsisSegment();

   inline int GetId() { return Id; }
   void SetCategoryId(int categoryID) { Category_ID = categoryID; }
   inline int GetCategoryId() { return Category_ID; }
   void AddCriteria(OsisCriteria* newCriteria);
   void AddDeduction(OsisDeduction* newDeduction);
   void AddMajorityDeduction(OsisMajorityDeduction* newMajorityDeduction);
   void AddOfficial(OsisOfficial* newOfficial);
   void AddPerformance(OsisPerformance* newPerformance);
   void AddElement(OsisElement* newElement);
   void AddWarmupGroup(OsisWarmupGroup* newWarmupGroup);
   void AddPrfRanking(OsisPrfRanking* newPrfRanking);

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
      qualified //
   };

   Q_ENUM(OsisElementAttributes)

private:
   int Id;
   int Category_ID;
   OsisCriteriaMap Criteries;
   OsisDeductionMap Deductions;
   OsisMajorityDeductionMap MajorityDeductions;
   OsisOfficialMap Officials;
   OsisPerformanceMap Performances;
   OsisPerformance* Current_Performance;
   OsisWarmupGroupMap WarmupGroups;
   OsisPrfRanking* Prf_Ranking;
};

typedef QMap <int, OsisSegment*> OsisSegmentMap;

#endif // OSISSEGMENT_H
