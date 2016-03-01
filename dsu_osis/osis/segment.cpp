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
   , Prf_Ranking(0)
   , Prf_Details(0)
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
   foreach (OsisPerformance* performance, Performances)
   {
      delete performance;
   }
   delete Prf_Ranking;
   delete Prf_Details;
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

void OsisSegment::AddWarmupGroup(OsisWarmupGroup* newWarmupGroup)
{
   if (newWarmupGroup && newWarmupGroup->GetIndex() != -1)
   {
      WarmupGroups.insert(newWarmupGroup->GetIndex(), newWarmupGroup);
   }
}

void OsisSegment::AddPrfRanking(OsisPrfRanking* newPrfRanking)
{
   if (newPrfRanking)
   {
      if (Prf_Ranking)
      {
         delete Prf_Ranking;
      }
      Prf_Ranking = newPrfRanking;
   }
}

void OsisSegment::AddPrfDetails(OsisPrfDetails* newPrfDetails)
{
   if (newPrfDetails)
   {
      if (Prf_Details)
      {
         delete Prf_Details;
      }
      Prf_Details = newPrfDetails;
   }
}
