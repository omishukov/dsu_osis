/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "warmupgroup.h"

OsisWarmupGroup::OsisWarmupGroup(QDomElement& osisElement, const char* elementName, QObject *parent)
   : QObject(parent)
   , OsisData(OsisWarmupGroup::staticMetaObject, osisElement, elementName)
   , Ind(GetAttributeInt(Index))
   , Num(GetAttributeInt(Number))
{
}
