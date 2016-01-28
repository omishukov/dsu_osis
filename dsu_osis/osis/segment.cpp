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

void OsisSegment::AddCriteria(OsisCriteria* newCriteria)
{
   Criteries.insert(newCriteria->GetIndex(), newCriteria);
}
