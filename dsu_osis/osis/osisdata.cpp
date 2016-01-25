/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include "osisdata.h"
#include <QMetaEnum>
#include <QDebug>

OsisData::OsisData(const QMetaObject& _mo, QString elementName)
   : mo(_mo)
   , ElementName(elementName)
{
}

int OsisData::getEnumKey(const char* enumTypeName, const char* enumName)
{
   QMetaEnum metaEnum = mo.enumerator(mo.indexOfEnumerator(enumTypeName));
   return metaEnum.keyToValue(enumName);
}

void OsisData::Update(OsisData& newData)
{
   Attribute.swap(newData.Attribute);

   Attribute = newData.Attribute;

}

QString OsisData::GetAttribute(int key)
{
   QString empty;
   return Attribute.find(key) != Attribute.end() ? Attribute[key] : empty;
}

bool OsisData::ProcessAttributes(QDomElement& criteriaElement)
{
   // Parse and save <Criteria> attributes
   QDomNamedNodeMap attr = criteriaElement.attributes();
   int size = attr.size();
   if (!size)
   {
      return false; // Error
   }

   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();
      QString value(at.value());
      int key = getEnumKey("OsisElementAttributes", at.name().toLocal8Bit().constData());

      if (key != -1)
      {
         if (Attribute.contains(key))
         {
            Attribute.remove(key);
         }
         Attribute[key] = value;
      }
      else
      {
         qCritical() << "<" << ElementName << ">:  Unknown attribute (" << value << ")" << endl;
      }
   }

   return true;
}
