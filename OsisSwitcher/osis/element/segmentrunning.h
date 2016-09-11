/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISSEGMENTRUNNING_H
#define OSISSEGMENTRUNNING_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Segment_Running Segment_ID="17">
 */

class OsisSegmentRunning : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Segment_ID, // ID of current segment
      Category_ID, // ID of current category
      Segment_Index //Number of current segment within current category
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisSegmentRunning(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int SegmentID;
};

#endif // OSISSEGMENTRUNNING_H
