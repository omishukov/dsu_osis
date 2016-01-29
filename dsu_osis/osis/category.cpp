/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "category.h"


OsisCategory::OsisCategory(QDomElement& categoryElement)
   : OsisData(OsisCategory::staticMetaObject, "Category")
{
   ProcessAttributes(categoryElement);

   bool ok;
   Id = GetAttribute(OsisCategory::ID).toInt(&ok);
   if (!ok)
   {
      Id = -1;
      qCritical() << "Invalid category ID: " << GetAttribute(OsisCategory::ID) << ", Name:" << GetAttribute(OsisCategory::Name) << endl;
   }
}

OsisCategory::~OsisCategory()
{
   // Segment and Participants are deleted from ISUCompetition object
}

void OsisCategory::AddSegment(OsisSegment* newSegment)
{
   Segments.insert(newSegment->GetId(), newSegment);
}

void OsisCategory::AddParticipant(OsisParticipant* newParticipant)
{
   Participants.insert(newParticipant->GetId(), newParticipant);
}
