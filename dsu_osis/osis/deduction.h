/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISDEDUCTION_H
#define OSISDEDUCTION_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

class OsisDeduction : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisDeduction(QObject *parent = 0);

public:
   enum OsisElementAttributes
   {
      Index, // Index, used as identifier
      Ded_Name, // 40
      Ded_Value, // Format “9.99”
      Ded_Edit
   };
   Q_ENUM(OsisElementAttributes)

   int GetIndex();
   QString GetName();
   double GetValue();
   QString GetEdit();

};

typedef QMap <int, OsisDeduction*> OsisDeductionMap;

#endif // OSISDEDUCTION_H
