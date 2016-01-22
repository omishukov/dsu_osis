/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QDomDocument>
#include <QMap>
#include "osisdata.h"

class OsisCategory: public QObject, public OsisData
{
   Q_OBJECT

public:
   OsisCategory();
   OsisCategory& operator=(const OsisCategory &category);

   int GetId() { return Category_ID; }
   int GetTecId() { return Category_Tec_Id; }
   QString GetName() { return Category_Name; }
   QString GetLevel() { return Category_Level; }
   QString GetGender() { return Category_Gender; }
   QString GetType() { return Category_Type; }
   QString GetExtDt() { return Category_ExtDt; }
   QString GetTypeName() { return Category_TypeName; }

   void ProcessAttribute(int key, QString& value);

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
      ExtDt // RSC Code
   };

   Q_ENUM(OsisElementAttributes)

private:
   int Category_ID;
   int Category_Tec_Id;
   QString Category_Name;
   QString Category_Level;
   QString Category_Gender;
   QString Category_Type;
   QString Category_ExtDt;
   QString Category_TypeName;
};

typedef QMap <int, OsisCategory*> OsisCategoryMap;

#endif // CATEGORY_H
