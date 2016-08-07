/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISCRITERIA_H
#define OSISCRITERIA_H

#include <QObject>
#include <QDomDocument>
#include <QMultiMap>
#include "osisdata.h"

/*
 *  <Criteria Index="1" Cri_Name="Skating Skills" Cri_Abbrev="SS" Cri_Factor="0.80"/>
 */

class OsisCriteria : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Index, //  Index, used as identifier
      Cri_Name, // 40
      Cri_Abbrev, // 10
      Cri_Factor, //  Format “9.99”
      Points //  Format “9.99”
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisCriteria(QDomElement& osisElement, const char* elementName, QObject *parent = 0);

   int Id;
};

typedef QMultiMap <int, OsisCriteria*> OsisCriteriaMap;

#endif // OSISCRITERIA_H
