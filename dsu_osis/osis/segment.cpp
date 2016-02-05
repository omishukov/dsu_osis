/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "segment.h"

OsisSegment::OsisSegment(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisSegment::staticMetaObject, "Segment")
   , Category_ID(-1)
   , Current_Performance(0)
{
   ProcessAttributes(osisElement);

   bool ok;
   Id = GetAttribute(OsisSegment::ID).toInt(&ok);
   if (!ok)
   {
      Id = -1;
      qCritical() << "Invalid segment ID: " << GetAttribute(OsisSegment::ID) << ", Name:" << GetAttribute(OsisSegment::Name) << endl;
   }
}

OsisSegment::~OsisSegment()
{
   foreach (OsisCriteria* criteria, Criteries)
   {
      delete criteria;
   }
   foreach (OsisDeduction* deduction, Deductions)
   {
      delete deduction;
   }
   foreach (OsisMajorityDeduction* mdeduction, MajorityDeductions)
   {
      delete mdeduction;
   }
}

void OsisSegment::AddCriteria(OsisCriteria* newCriteria)
{
   if (newCriteria && newCriteria->GetIndex() != -1)
   {
      Criteries.insert(newCriteria->GetIndex(), newCriteria);
   }
}

void OsisSegment::AddDeduction(OsisDeduction* newDeduction)
{
   if (newDeduction && newDeduction->GetIndex() != -1)
   {
      Deductions.insert(newDeduction->GetIndex(), newDeduction);
   }
}

void OsisSegment::AddMajorityDeduction(OsisMajorityDeduction* newMajorityDeduction)
{
   if (newMajorityDeduction && newMajorityDeduction->GetIndex() != -1)
   {
      MajorityDeductions.insert(newMajorityDeduction->GetIndex(), newMajorityDeduction);
   }
}

void OsisSegment::AddOfficial(OsisOfficial* newOfficial)
{
   if (newOfficial && newOfficial->GetIndex() != -1)
   {
      Officials.insert(newOfficial->GetIndex(), newOfficial);
   }
}

void OsisSegment::AddPerformance(OsisPerformance* newPerformance)
{
   if (newPerformance && newPerformance->GetId() != -1)
   {
      int Id = newPerformance->GetId();
      if (Performances.contains(Id))
      {
         Performances.value(Id)->Update(*newPerformance);
         delete newPerformance;
      }
      else
      {
         Performances.insert(Id, newPerformance);
      }
      Current_Performance = Performances[Id];
   }
}

void OsisSegment::AddElement(OsisElement* newElement)
{
   if (Current_Performance && Current_Performance->GetId() != -1)
   {
      Current_Performance->AddElement(newElement);
   }
}
