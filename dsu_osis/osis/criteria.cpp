/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "criteria.h"

OsisCriteria::OsisCriteria(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisCriteria::staticMetaObject, "Criteria")
{
   ProcessAttributes(osisElement);

   bool ok;
   Ind = GetAttribute(OsisCriteria::Index).toInt(&ok);
   if (!ok)
   {
      Ind = -1;
      qCritical() << "Invalid Criteria Index: " << GetAttribute(OsisCriteria::Index) << ", Name:" << GetAttribute(OsisCriteria::Cri_Name) << endl;
   }
}
