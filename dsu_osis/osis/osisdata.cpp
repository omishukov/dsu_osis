/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include "osisdata.h"
#include <QMetaEnum>

OsisData::OsisData(const QMetaObject& _mo)
   : mo(_mo)
{
}

int OsisData::getEnumKey(const char* enumTypeName, const char* enumName)
{
   QMetaEnum metaEnum = mo.enumerator(mo.indexOfEnumerator(enumTypeName));
   return metaEnum.keyToValue(enumName);
}
