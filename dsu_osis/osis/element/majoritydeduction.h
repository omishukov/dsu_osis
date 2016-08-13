/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISMAJORITYDEDUCTION_H
#define OSISMAJORITYDEDUCTION_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

/*
 * <Majority_Deduction Index="1" Ded_Index="1"/>
 */

class OsisMajorityDeduction : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Index, // Index, used as identifier
      Ded_Index,
      Ded_Count
   };
   Q_ENUM(OsisElementAttributes)


public:
   explicit OsisMajorityDeduction(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int Ind;
};

typedef QMap <int, OsisMajorityDeduction*> OsisMajorityDeductionMap;

#endif // OSISMAJORITYDEDUCTION_H
