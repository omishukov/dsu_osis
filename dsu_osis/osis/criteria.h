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
   explicit OsisCriteria(int segmentId, QObject *parent = 0);
   OsisCriteria& operator=(const OsisCriteria &copy);

   int GetSegmentId() { return SegmentId; }
   int GetIndex() { return CriIndex; }
   QString GetName() { return CriName; }
   QString GetAbbrev() { return CriAbbrev; }
   double GetFactor() { return CriFactor; }
   double GetPoints() { return CriPoints; }

   void ProcessAttribute(int key, QString& value);

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

signals:

public slots:

private:
   int SegmentId;
   int CriIndex;
   QString CriName;
   QString CriAbbrev;
   double CriFactor;
   double CriPoints;

};

typedef QMap <int, OsisCriteria*> OsisCriteriaMap;

#endif // OSISCRITERIA_H
