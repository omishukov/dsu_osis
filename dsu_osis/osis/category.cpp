/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "category.h"


OsisCategory::OsisCategory()
   : OsisData(OsisCategory::staticMetaObject, "Category")
{
}

int OsisCategory::GetId()
{
   return GetAttributeInt(ID);
}

int OsisCategory::GetTecId()
{
   return GetAttributeInt(Tec_Id);
}

int OsisCategory::Gettecid()
{
   return GetAttributeInt(tec_id);
}

QString OsisCategory::GetName()
{
   return GetAttribute(Name);
}

QString OsisCategory::GetLevel()
{
   return GetAttribute(Level);
}

QString OsisCategory::GetGender()
{
   return GetAttribute(Gender);
}

QString OsisCategory::GetType()
{
   return GetAttribute(Type);
}

QString OsisCategory::GetExtDt()
{
   return GetAttribute(ExtDt);
}

QString OsisCategory::GetTypeName()
{
   return GetAttribute(TypeName);
}
