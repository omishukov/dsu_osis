/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISDATA_H
#define OSISDATA_H

#include <QDomDocument>
#include <QMap>

class OsisData
{
public:
   OsisData(const QMetaObject &_mo, QString elementName);

   virtual bool ProcessAttributes(QDomElement& osisElement);
   int getEnumKey(const char* enumTypeName, const char* enumName);
   void Update(OsisData& newData);

private:
   const QMetaObject &mo;

protected:

   QString GetAttribute(int key);
   int GetAttributeInt(int key);
   double GetAttributeDouble(int key);

private:
   QMap<int, QString> Attribute;
   QString ElementName;
};

#endif // OSISDATA_H
