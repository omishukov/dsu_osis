/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDomDocument>
#include <QMetaEnum>
#include "event.h"
#include "deduction.h"
#include "participant.h"

OsisEvent::OsisEvent(QDomElement& eventElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisEvent::staticMetaObject, "Event")
   , event_ODF(-1)
{
   ProcessAttributes(eventElement);

   bool ok;
   event_ID = GetAttribute(OsisEvent::ID).toInt(&ok);
   if (!ok)
   {
      event_ID = -1;
   }
   event_Name = GetAttribute(OsisEvent::Name);
   event_Abbreviation = GetAttribute(OsisEvent::Abbreviation);
   event_Type = GetAttribute(OsisEvent::Type);
   event_CmpType = GetAttribute(OsisEvent::CmpType);
   event_ExtDt = GetAttribute(OsisEvent::ExtDt);
   event_ODF = GetAttribute(OsisEvent::ODF).toInt(&ok);
   if (!ok)
   {
      event_ODF = -1;
   }
}

OsisEvent::~OsisEvent()
{

}
#if 0
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

   if (!newCriteria->ProcessAttributes(criteriaElement))
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

   if (!newDeduction->ProcessAttributes(deductionElement))
   {
      return false;
   }

   si.value()->InsertDeduction(newDeduction);

   return true;
}
#endif
void OsisEvent::ProcessingDone()
{
   Current_Category = -1;
   Current_Segment = -1;
}
