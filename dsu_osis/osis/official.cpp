/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QDebug>
#include <QMetaEnum>
#include "official.h"

OsisOfficial::OsisOfficial(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisOfficial::staticMetaObject, "Official")
{
   ProcessAttributes(osisElement);

   bool ok;
   Ind = GetAttribute(OsisOfficial::Index).toInt(&ok);
   if (!ok)
   {
      Ind = -1;
      qCritical() << "Invalid Official Index: " << GetAttribute(OsisOfficial::Index) << ", Name:" << GetAttribute(OsisOfficial::Full_Name) << endl;
   }
}