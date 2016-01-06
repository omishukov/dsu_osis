/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDomDocument>
#include <QMetaEnum>
#include "event.h"
#include "deduction.h"

OsisEvent::OsisEvent()
   : event_ID(-1),
     event_ODF(-1),
     Current_Category(-1),
     Current_Segment(-1),
     ActiveSegment(0)
{
}

OsisEvent::~OsisEvent()
{
   if (ActiveSegment)
   {
      delete ActiveSegment;
   }
   foreach (OsisCategory* category, CategoryMap)
   {
      delete category;
   }
   foreach (OsisSegment* segment, SegmentMap)
   {
      delete segment;
   }
}

bool OsisEvent::ProcessEvent(QDomElement &eventElement)
{
   // Parse and save <Event> attributes
   QDomNamedNodeMap attr = eventElement.attributes();
   int size = attr.size();
   if (!size)
   {
      return false; // Error
   }

   const QMetaObject &mo = OsisEvent::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisEventAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);
   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();

      switch (metaEnum.keyToValue(at.name().toLocal8Bit().constData()))
      {
         case ID:
            event_ID = at.value().toInt();
            break;
         case Name:
            event_Name = at.value();
            break;
         case Abbreviation:
            event_Abbreviation = at.value();
            break;
         case Type:
            event_Type = at.value();
            break;
         case CmpType:
            event_CmpType = at.value();
            break;
         case ExtDt:
            event_ExtDt = at.value();
            break;
         case ODF:
            event_ODF = at.value().toInt();
            break;
         default:
            break;
      }
   }

   return true;
}

bool OsisEvent::ProcessCategory(QDomElement& categoryElement)
{
   OsisCategory* newCategory = new OsisCategory();

   if (!newCategory->ProcessCategoryAttributes(categoryElement))
   {
      return false; // Report Error: Invalid Category attributes
   }

   Current_Category = newCategory->GetId();
   if (Current_Category == -1)
   {
      return false; // Report Warning: Invalid Category
   }

   if (CategoryMap.contains(Current_Category))
   {
      OsisCategory* existingCategory = CategoryMap.value(Current_Category);
      *existingCategory = *newCategory;
      delete newCategory;
   }
   else
   {
      CategoryMap.insert(Current_Category, newCategory);
   }

   return true;
}

bool OsisEvent::ProcessSegmentStart(QDomElement& e)
{
   OsisSegmentStart* segmentStart = new OsisSegmentStart();

   if (!segmentStart->ProcessSegmentStartAttributes(e))
   {
      return false;
   }

   if (ActiveSegment)
   {
      delete ActiveSegment;
   }

   ActiveSegment = segmentStart;

   return true;
}


bool OsisEvent::ProcessSegment(QDomElement& e)
{
   if (Current_Category == -1)
   {
      return false;
   }

   OsisSegment* newSegment = new OsisSegment(Current_Category);

   if (!newSegment->ProcessSegmentAttributes(e))
   {
      return false; // Error in Segment attributes
   }

   int SegmentId = newSegment->GetID();

   if (SegmentId == -1)
   {
      return false; // Report Warning: Invalid Category
   }
   else
   {
      if (SegmentMap.contains(SegmentId))
      {
         OsisSegment* existingSegment = SegmentMap.value(SegmentId);
         *existingSegment = *newSegment;
         delete newSegment;
      }
      else
      {
         SegmentMap.insert(SegmentId, newSegment);
      }
   }
   return true;
}

bool OsisEvent::ProcessCriteria(QDomElement& criteriaElement)
{
   if (Current_Segment == -1)
   {
      return false;
   }

   OsisSegmentMap::iterator si = SegmentMap.find(Current_Segment);
   if (si == SegmentMap.end())
   {
      return false;
   }

   OsisCriteria* newCriteria = new OsisCriteria(Current_Segment);

   if (!newCriteria->ProcessCriteriaAttributes(criteriaElement))
   {
      return false; // Error in Segment attributes
   }

   si.value()->InsertCriteria(newCriteria);

   return true;
}

bool OsisEvent::ProcessDeduction(QDomElement& deductionElement)
{
   if (Current_Segment == -1)
   {
      return false;
   }

   OsisSegmentMap::iterator si = SegmentMap.find(Current_Segment);
   if (si == SegmentMap.end())
   {
      return false;
   }
   OsisDeduction* newDeduction = new OsisDeduction();

   if (!newDeduction->ProcessDeductionAttributes(deductionElement))
   {
      return false;
   }

   si.value()->InsertDeduction(newDeduction);

   return true;
}

bool OsisEvent::ProcessParticipant(QDomElement& participantElement)
{
   if (ActiveSegment->GetSegmentId() == -1)
   {
      return false;
   }

}

void OsisEvent::ProcessingDone()
{
   Current_Category = -1;
   Current_Segment = -1;
}
