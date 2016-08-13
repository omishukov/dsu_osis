/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISELEMENTLIST_H
#define OSISELEMENTLIST_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Element_List Confirmed="1" NoOfCountingElements="6">
 */

class OsisElementList : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Confirmed,
      NoOfCountingElements
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisElementList(QDomElement& osisElement, QString& elementName, QObject *parent = 0);
};

#endif // OSISELEMENTLIST_H
