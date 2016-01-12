/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISSEGMENT_H
#define OSISSEGMENT_H

#include <QObject>
#include <QDomDocument>
#include "criteria.h"
#include "deduction.h"

class OsisSegment : public QObject
{
   Q_OBJECT
public:
   explicit OsisSegment(int category, QObject *parent = 0);
   OsisSegment& operator=(const OsisSegment &copy);
   ~OsisSegment();

   int GetID() { return Segment_ID;}
   QString GetName() { return Segment_Name;}
   QString GetAbbreviation() { return Segment_Abbreviation;}
   QString GetName_Of_Dance() { return Segment_Name_Of_Dance;}
   QString GetType() { return Segment_Type;}
   int GetNumber_Of_Judges() { return Segment_Number_Of_Judges; }
   int GetNumber_Of_Decisive_Judges() { return Segment_Number_Of_Decisive_Judges;}
   QString GetQCrit() { return Segment_QCrit;}
   int GetQNumber() { return Segment_QNumber;}
   QString GetDate() { return Segment_Date;}
   QString GetStart() { return Segment_Start;}
   QString GetStatus() { return Segment_Status;}
   QString GetEnd() { return Segment_End;}
   QString GetExtDt() { return Segment_ExtDt;}
   int GetMedal() { return Segment_Medal;}
   QString Getqualified() { return Segment_qualified;}

   bool ProcessSegmentAttributes(QDomElement& segmentElement);
   void InsertCriteria(OsisCriteria* criteria);
   OsisCriteria* GetCriteria(int index);
   void InsertDeduction(OsisDeduction* deduction);
   OsisDeduction* GetDeduction(int index);

public:
   enum OsisSegmentAttributes
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

   Q_ENUM(OsisSegmentAttributes)

private:
   int Category_ID;
   int Segment_ID;
   QString Segment_Name;
   QString Segment_Abbreviation;
   QString Segment_Name_Of_Dance;
   QString Segment_Type;
   int Segment_Number_Of_Judges;
   int Segment_Number_Of_Decisive_Judges;
   QString Segment_QCrit;
   int Segment_QNumber;
   QString Segment_Date;
   QString Segment_Start;
   QString Segment_Status;
   QString Segment_End;
   QString Segment_ExtDt;
   int Segment_Medal;
   QString Segment_qualified;

   OsisCriteriaMap CriteriaMap;
   OsisDeductionMap DeductionMap;
};

typedef QMap <int, OsisSegment*> OsisSegmentMap;

#endif // OSISSEGMENT_H
