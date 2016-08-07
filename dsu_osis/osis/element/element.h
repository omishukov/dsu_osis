/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef OSISELEMENT_H
#define OSISELEMENT_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

/*
 * <Element Index="1" PName="2Lz+2T" PBVal="3.40"/>
 * <Element Index="1" Elm_Name="1Lz*+1T*" Points="0.00" Elm_XBV="0.00" Elm_XGOE="0.00" Elm_Info="*" Elm_Half="1"/>
 */

class OsisElement : public QObject, public OsisData
{
   Q_OBJECT
public:
   enum OsisElementAttributes
   {
      Index, //Index, used as identifier
      Elm_Name, // 80
      Elm_Time, // 4, Time within the program
      Elm_Invalid, // 0 or 1, 1 if base value = 0
      PName, // 80, Name of planned element (without level)
      PBVal, // 20, Base value of planned element, Format “9.9”, Based on level 1
      Points, // Score of the element, Format “9.99”
      Elm_XBV, // Base value of executed element Format “9.99”
      Elm_XGOE, // Grade of execution of element Format “9.99”
      Elm_Info, // 5, Element info (e.g. wrong edge)
      Elm_Half // 1 – for element not in second half 2 – for element in second half
   };
   Q_ENUM(OsisElementAttributes)

public:
   explicit OsisElement(QDomElement& osisElement, const char* elementName, QObject *parent = 0);

   int Ind;
};

typedef QMap <int, OsisElement*> OsisElementMap;

#endif // OSISELEMENT_H
