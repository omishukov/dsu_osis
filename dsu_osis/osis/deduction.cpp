/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include <QDebug>
#include "deduction.h"

OsisDeduction::OsisDeduction(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisDeduction::staticMetaObject, "Deduction")
{
   ProcessAttributes(osisElement);

   bool ok;
   Ind = GetAttribute(OsisDeduction::Index).toInt(&ok);
   if (!ok)
   {
      Ind = -1;
      qCritical() << "Invalid Deduction Index: " << GetAttribute(OsisDeduction::Index) << ", Name:" <<GetAttribute(OsisDeduction::Ded_Name) << endl;
   }
}
