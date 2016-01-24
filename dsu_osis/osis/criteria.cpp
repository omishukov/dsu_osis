/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "criteria.h"

OsisCriteria::OsisCriteria(int segmentId, QObject *parent)
   : QObject(parent)
   , OsisData(OsisCriteria::staticMetaObject, "Criteria")
   , SegmentId(segmentId)
{
}

int OsisCriteria::GetSegmentId()
{
   return SegmentId;
}

int OsisCriteria::GetIndex()
{
   return GetAttributeInt(Index);
}

QString OsisCriteria::GetName()
{
   return GetAttribute(Cri_Name);
}

QString OsisCriteria::GetAbbrev()
{
   return GetAttribute(Cri_Abbrev);
}

double OsisCriteria::GetFactor()
{
   return GetAttributeDouble(Cri_Factor);
}

double OsisCriteria::GetPoints()
{
   return GetAttributeDouble(Points);
}

