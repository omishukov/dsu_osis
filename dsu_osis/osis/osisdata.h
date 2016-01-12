/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISDATA_H
#define OSISDATA_H

#include <QDomDocument>

class OsisData
{
public:
   OsisData(const QMetaObject &_mo);

   virtual bool ProcessAttributes(QDomElement& osisElement) = 0;

   int getEnumKey(const char* enumTypeName, const char* enumName);

private:
   const QMetaObject &mo;
};

#endif // OSISDATA_H
