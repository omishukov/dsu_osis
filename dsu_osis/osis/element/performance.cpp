/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "performance.h"

OsisPerformance::OsisPerformance(QDomElement& categoryElement, const char* elementName, QObject *parent)
   : QObject(parent)
   , OsisData(OsisPerformance::staticMetaObject, categoryElement, elementName)
   , Id(GetAttributeInt(ID))
{
}

//void OsisPerformance::AddElement(OsisElement* newElement)
//{
//   if (newElement && newElement->GetIndex() != -1)
//   {
//      int Ind = newElement->GetIndex();
//      if (Elements.contains(Ind))
//      {
//         Elements.value(Ind)->Update(newElement);
//         delete newElement;
//      }
//      else
//      {
//         Elements.insert(Ind, newElement);
//      }
//   }
//}
