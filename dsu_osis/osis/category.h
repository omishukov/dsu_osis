#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>
#include <QDomDocument>
#include <QMap>

class OsisCategory: public QObject
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

   bool ProcessCategoryAttributes(QDomElement& categoryElement);

public:
   enum OsisCategoryAttributes
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

   Q_ENUM(OsisCategoryAttributes)

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
