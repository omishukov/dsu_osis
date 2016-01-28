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
#include "segment.h"
#include "participant.h"

class OsisCategory: public QObject, public OsisData
{
   Q_OBJECT
public:
   OsisCategory(QDomElement& categoryElement);

   inline int GetId() { return Id; }
   void AddSegment(OsisSegment* newSegment);
   void AddParticipant(OsisParticipant* newParticipant);

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

private:
   int Id;
   OsisSegmentMap Segments;
   OsisParticipantMap Participants;

};

typedef QMap <int, OsisCategory*> OsisCategoryMap;

#endif // CATEGORY_H
