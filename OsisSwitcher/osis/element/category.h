/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QMap>
#include "osisdata.h"

/*
 * <Category ID="14" Name="Novice Piger M" Level="NAD" Gender="F" Type="SGL" tec_id="0" ExtDt="" TypeName="Ladies">
 */

class OsisCategory: public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      ID, // Identifier
      Name, // e.g. Ladies, Men, Pairs, Ice Dancing
      Level, // See category level code
      Gender, // See category gender code
      Type, // See category type code
      TypeName, // ???
      Tec_Id, // -
      tec_id, // -
      ExtDt, // RSC Code
      LAST_ATTRIBUTE
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisCategory(QDomElement& categoryElement, QString& elementName, QObject *parent = 0);

   int Id;
};

typedef QMap <int, OsisCategory*> OsisCategoryMap;

#endif // CATEGORY_H
