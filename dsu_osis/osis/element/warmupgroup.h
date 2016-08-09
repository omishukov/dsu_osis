/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISWARMUPGROUP_H
#define OSISWARMUPGROUP_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

/*
 * <Warmup_Group Index="0" Number="5"/>
 */

class OsisWarmupGroup : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Index,
      Number // Number of participants in Warmup-Group
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisWarmupGroup(QDomElement& osisElement, const char* elementName, QObject *parent = 0);

   int Ind;
   int Num;
   int SegmentId;
};

typedef QMap <int, OsisWarmupGroup*> OsisWarmupGroupMap;

#endif // OSISWARMUPGROUP_H
