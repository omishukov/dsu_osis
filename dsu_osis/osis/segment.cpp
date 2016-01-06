/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "segment.h"

OsisSegment::OsisSegment(int category, QObject *parent)
   : QObject(parent)
   , Category_ID(category)
   , Segment_ID(-1)
   , Segment_Number_Of_Judges(-1)
   , Segment_Number_Of_Decisive_Judges(-1)
   , Segment_QNumber(-1)
   , Segment_Medal(-1)
{
}

OsisSegment& OsisSegment::operator=(const OsisSegment& copy)
{
   if (this == &copy)
   {
      return *this;
   }
   if (copy.Category_ID != -1)
   {
      Category_ID = copy.Category_ID;
   }
   if (copy.Segment_ID != -1)
   {
      Segment_ID = copy.Segment_ID;
   }
   if (!copy.Segment_Name.isNull())
   {
      Segment_Name = copy.Segment_Name;
   }
   if (!copy.Segment_Abbreviation.isNull())
   {
      Segment_Abbreviation = copy.Segment_Abbreviation;
   }
   if (!copy.Segment_Name_Of_Dance.isNull())
   {
      Segment_Name_Of_Dance = copy.Segment_Name_Of_Dance;
   }
   if (!copy.Segment_Type.isNull())
   {
      Segment_Type = copy.Segment_Type;
   }
   if (copy.Segment_Number_Of_Judges != -1)
   {
      Segment_Number_Of_Judges = copy.Segment_Number_Of_Judges;
   }
   if (copy.Segment_Number_Of_Decisive_Judges != -1)
   {
      Segment_Number_Of_Decisive_Judges = copy.Segment_Number_Of_Decisive_Judges;
   }
   if (!copy.Segment_QCrit.isNull())
   {
      Segment_QCrit = copy.Segment_QCrit;
   }
   if (copy.Segment_QNumber != -1)
   {
      Segment_QNumber = copy.Segment_QNumber;
   }
   if (!copy.Segment_Date.isNull())
   {
      Segment_Date = copy.Segment_Date;
   }
   if (!copy.Segment_Start.isNull())
   {
      Segment_Start = copy.Segment_Start;
   }
   if (!copy.Segment_Status.isNull())
   {
      Segment_Status = copy.Segment_Status;
   }
   if (!copy.Segment_End.isNull())
   {
      Segment_End = copy.Segment_End;
   }
   if (!copy.Segment_ExtDt.isNull())
   {
      Segment_ExtDt = copy.Segment_ExtDt;
   }
   if (copy.Segment_Medal != -1)
   {
      Segment_Medal = copy.Segment_Medal;
   }
   if (!copy.Segment_qualified.isNull())
   {
      Segment_qualified = copy.Segment_qualified;
   }
   return *this;
}

OsisSegment::~OsisSegment()
{
   foreach (OsisCriteria* criteria, CriteriaMap)
   {
      delete criteria;
   }

   foreach (OsisDeduction* deduction, DeductionMap)
   {
      delete deduction;
   }
}

bool OsisSegment::ProcessSegmentAttributes(QDomElement& segmentElement)
{
   const QMetaObject &mo = OsisSegment::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisSegmentAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);

   // Parse and save <Segment> attributes
   QDomNamedNodeMap attr = segmentElement.attributes();
   int size = attr.size();
   if (!size)
   {
      return false; // Error
   }

   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();

      switch (metaEnum.keyToValue(at.name().toLocal8Bit().constData()))
      {
         case ID:
            Segment_ID = at.value().toInt();
            break;
         case Name:
            Segment_Name = at.value();
            break;
         case Abbreviation:
            Segment_Abbreviation = at.value();
            break;
         case Name_Of_Dance:
            Segment_Name_Of_Dance = at.value();
            break;
         case Type:
            Segment_Type = at.value();
            break;
         case Number_Of_Judges:
            Segment_Number_Of_Judges  = at.value().toInt();
            break;
         case Number_Of_Decisive_Judges:
            Segment_Number_Of_Decisive_Judges = at.value().toInt();
            break;
         case QCrit:
            Segment_QCrit = at.value();
            break;
         case QNumber:
            Segment_QNumber = at.value().toInt();
            break;
         case Date:
            Segment_Date = at.value();
            break;
         case Start:
            Segment_Start = at.value();
            break;
         case Status:
            Segment_Status = at.value();
            break;
         case End:
            Segment_End = at.value();
            break;
         case ExtDt:
            Segment_ExtDt = at.value();
            break;
         case Medal:
            Segment_Medal = at.value().toInt();
            break;
         case qualified:
            Segment_qualified = at.value();
            break;
         default:
            // Warning: unknown <Segment> attribute
            break;
      }
   }

   return true;
}

void OsisSegment::InsertCriteria(OsisCriteria* criteria)
{
   if (!criteria || criteria->GetIndex() == -1)
   {
      return;
   }
   if (CriteriaMap.contains(criteria->GetIndex()))
   {
      OsisCriteria* existingCriteria = CriteriaMap.value(criteria->GetIndex());
      delete existingCriteria;
   }
   CriteriaMap.insert(criteria->GetIndex(), criteria);
}

OsisCriteria*OsisSegment::GetCriteria(int index)
{
   return CriteriaMap.value(index, NULL);
}

void OsisSegment::InsertDeduction(OsisDeduction* deduction)
{
   if (!deduction || deduction->GetIndex() == -1)
   {
      return;
   }
   if (DeductionMap.contains(deduction->GetIndex()))
   {
      OsisDeduction* existingDeduction = DeductionMap.value(deduction->GetIndex());
      delete existingDeduction;
   }

   DeductionMap.insert(deduction->GetIndex(), deduction);
}

OsisDeduction*OsisSegment::GetDeduction(int index)
{
   return DeductionMap.value(index, NULL);
}
