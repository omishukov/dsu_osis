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

/*
 * <Segment_Start Category_ID="14" Segment_ID="17" Segment_Index="1" Starting_Participant="1" Next_Participant="2" LastFinished_Participant="0">
 */

class OsisSegmentStart : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Segment_ID, // ID of current segment
      Category_ID, // ID of current category
      Segment_Index, // Number of current segment within current category
      Starting_Participant,
      Next_Participant,
      LastFinished_Participant
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisSegmentStart(QDomElement& osisElement, QString& elementName, QObject *parent = 0);

   int SegmentId;
   int CategoryId;
};

#endif // OSISSEGMENTSTART_H
