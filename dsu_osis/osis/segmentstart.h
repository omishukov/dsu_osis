/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISSEGMENTSTART_H
#define OSISSEGMENTSTART_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

class OsisSegmentStart : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisSegmentStart(QDomElement& segmentStartElement, QObject *parent = 0);

public:
   enum OsisSegmentStartAttributes
   {
      Segment_ID, // ID of current segment
      Category_ID, // ID of current category
      Segment_Index, // Number of current segment within current category
      Starting_Participant,
      Next_Participant,
      LastFinished_Participant
   };
   Q_ENUM(OsisSegmentStartAttributes)


signals:

public slots:
};

#endif // OSISSEGMENTSTART_H
