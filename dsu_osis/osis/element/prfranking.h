/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISPRFRANKING_H
#define OSISPRFRANKING_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Prf_Ranking Gender="F" Type="SGL" Rank="TO" TypeName="Ladies"/>
 */

class OsisPrfRanking : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Gender, // M|F|X
      Type, // See category types
      Rank, // See ranking type
      TypeName
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisPrfRanking(QDomElement& categoryElement, const char* elementName, QObject *parent = 0);
};

#endif // OSISPRFRANKING_H
