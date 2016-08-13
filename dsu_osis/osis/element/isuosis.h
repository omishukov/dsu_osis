/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef ISUOSIS_H
#define ISUOSIS_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Isu_Osis Part="1" version="2.0" Counter="1" IsuCalcFs="3.1.2" Database="11139">
 */

class IsuOsis : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Part, // 1 (public) | 2 (private)
      Version,
      Counter, // Not used
      IsuCalcFs, // ISUCalcFS version
      Database // Database version
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit IsuOsis(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int DatabaseId;
};

#endif // ISUOSIS_H
