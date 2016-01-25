/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISCRITERIA_H
#define OSISCRITERIA_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

class OsisCriteria : public QObject, public OsisData
{
   Q_OBJECT
public:
   explicit OsisCriteria(QDomElement& osisElement, QObject *parent = 0);

   void SetSegmentId(int segmentId) { SegmentId = segmentId; }
   int GetSegmentId() { return SegmentId; }

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

private:
   int SegmentId;

};

typedef QMap <int, OsisCriteria*> OsisCriteriaMap;

#endif // OSISCRITERIA_H
