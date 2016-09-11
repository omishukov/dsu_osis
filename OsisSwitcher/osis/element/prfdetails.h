/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISPRFDETAILS_H
#define OSISPRFDETAILS_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Prf_Details Points="19.18" TES="9.64" TCS="9.54" Bonus="0.00" Ded_Sum="0.00">
 */

class OsisPrfDetails : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Points, // Score of the performance, total segment score
      TES, // Technical element score. Format “9.99”
      TCS, // Total component score. Format “9.99”
      Bonus, //
      Ded_Sum, // Sum of all deductions
      Rec // 2. “PB” – personal best
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisPrfDetails(QDomElement& categoryElement, QString& elementName, QObject *parent = 0);

};

#endif // OSISPRFDETAILS_H
