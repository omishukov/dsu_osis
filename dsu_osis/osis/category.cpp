/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "category.h"


OsisCategory::OsisCategory()
   : OsisData(OsisCategory::staticMetaObject)
   , Category_ID(-1)
   , Category_Tec_Id(-1)
{

}

OsisCategory& OsisCategory::operator=(const OsisCategory& copy)
{
   if (this == &copy)
   {
      return *this;
   }

   if (copy.Category_ID != -1)
   {
      Category_ID = copy.Category_ID;
   }
   if (copy.Category_Tec_Id != -1)
   {
      Category_Tec_Id = copy.Category_Tec_Id;
   }
   if (!copy.Category_Name.isNull())
   {
      Category_Name = copy.Category_Name;
   }
   if (!copy.Category_Level.isNull())
   {
      Category_Level = copy.Category_Level;
   }
   if (!copy.Category_Gender.isNull())
   {
      Category_Gender = copy.Category_Gender;
   }
   if (!copy.Category_Type.isNull())
   {
      Category_Type = copy.Category_Type;
   }
   if (!copy.Category_ExtDt.isNull())
   {
      Category_ExtDt = copy.Category_ExtDt;
   }
   if (!copy.Category_TypeName.isNull())
   {
      Category_TypeName = copy.Category_TypeName;
   }

   return *this;
}

void OsisCategory::ProcessAttribute(int key, QString& value)
{
   switch (static_cast<enum OsisElementAttributes>(key))
   {
      case ID:
         Category_ID = value.toInt();
         break;
      case Name:
         Category_Name = value;
         break;
      case Level:
         Category_Level = value;
         break;
      case Gender:
         Category_Gender = value;
         break;
      case Type:
         Category_Type = value;
         break;
      case TypeName:
         Category_TypeName = value;
         break;
      case Tec_Id:
      case tec_id:
         Category_Tec_Id = value.toInt();
         break;
      case ExtDt:
         Category_ExtDt = value;
         break;
      default:
         break;
   }
}
