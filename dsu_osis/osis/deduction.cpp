/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include <QMetaEnum>
#include "deduction.h"

OsisDeduction::OsisDeduction(QObject *parent)
   : QObject(parent)
   , OsisData(OsisDeduction::staticMetaObject, "Deduction")
{
}

int OsisDeduction::GetIndex()
{
   return GetAttributeInt(Index);
}

QString OsisDeduction::GetName()
{
   return GetAttribute(Ded_Name);
}

double OsisDeduction::GetValue()
{
   return GetAttributeDouble(Ded_Value);
}

QString OsisDeduction::GetEdit()
{
   return GetAttribute(Ded_Edit);
}
