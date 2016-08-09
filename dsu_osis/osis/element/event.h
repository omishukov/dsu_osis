/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDomDocument>
#include "osisdata.h"

/*
 * <Event ID="1" Name="Efterårskonkurrencen 2015" Abbreviation="EK15" Type="T" CmpType="P" ExtDt="">
 */

class OsisEvent: public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      ID, // Identifier
      Name, //
      Abbreviation, //
      Type, // Type of the event, standard value: “T”
      CmpType, // Competition type
      ExtDt, // Results System Codes
      ODF // ???
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisEvent(QDomElement& osisElement, const char* elementName, QObject *parent = 0);

   int Id;
};

#endif // EVENT_H
