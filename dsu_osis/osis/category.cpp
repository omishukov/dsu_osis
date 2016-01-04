#include <QMetaEnum>
#include "category.h"


OsisCategory::OsisCategory()
   : Category_ID(-1),
     Category_Tec_Id(-1)
{

}

bool OsisCategory::ProcessCategoryAttributes(QDomElement& categoryElement)
{
   const QMetaObject &mo = OsisCategory::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisCategoryAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);

   // Parse and save <Category> attributes
   QDomNamedNodeMap attr = categoryElement.attributes();
   int size = attr.size();
   if (!size)
   {
      return false; // Error
   }

   for (int i = 0; i < size; i++)
   {
      QDomAttr at = attr.item(i).toAttr();

      switch (metaEnum.keyToValue(at.name().toLocal8Bit().constData()))
      {
         case ID:
            Category_ID = at.value().toInt();
            break;
         case Name:
            Category_Name = at.value();
            break;
         case Level:
            Category_Level = at.value();
            break;
         case Gender:
            Category_Gender = at.value();
            break;
         case Type:
            Category_Type = at.value();
            break;
         case TypeName:
            Category_TypeName = at.value();
            break;
         case Tec_Id:
         case tec_id:
            Category_Tec_Id = at.value().toInt();
            break;
         case ExtDt:
            Category_ExtDt = at.value();
            break;
         default:
            break;
      }
   }

   return true;
}


OsisCategory& OsisCategory::operator=(const OsisCategory& copy)
{
   if (this == &copy)
   {
      return *this;
   }

   if (copy.Category_ID != -1)
   {
      Category_ID = copy.Category_ID;
   }
   if (copy.Category_Tec_Id != -1)
   {
      Category_Tec_Id = copy.Category_Tec_Id;
   }
   if (!copy.Category_Name.isNull())
   {
      Category_Name = copy.Category_Name;
   }
   if (!copy.Category_Level.isNull())
   {
      Category_Level = copy.Category_Level;
   }
   if (!copy.Category_Gender.isNull())
   {
      Category_Gender = copy.Category_Gender;
   }
   if (!copy.Category_Type.isNull())
   {
      Category_Type = copy.Category_Type;
   }
   if (!copy.Category_ExtDt.isNull())
   {
      Category_ExtDt = copy.Category_ExtDt;
   }
   if (!copy.Category_TypeName.isNull())
   {
      Category_TypeName = copy.Category_TypeName;
   }

   return *this;
}
