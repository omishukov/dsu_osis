#include <QMetaEnum>
#include "deduction.h"

OsisDeduction::OsisDeduction(QObject *parent)
   : QObject(parent)
   , DedIndex(-1)
   , DedValue(-1)
{

}

bool OsisDeduction::ProcessDeductionAttributes(QDomElement& deductionElement)
{
   const QMetaObject &mo = OsisDeduction::staticMetaObject;
   int index = mo.indexOfEnumerator("OsisDeductionAttributes");
   QMetaEnum metaEnum = mo.enumerator(index);

   // Parse and save <Deduction> attributes
   QDomNamedNodeMap attr = deductionElement.attributes();
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
         case Index:
            DedIndex = at.value().toInt();
            break;
         case Ded_Name:
            DedName = at.value();
            break;
         case Ded_Edit:
            DedEdit = at.value();
            break;
         case Ded_Value:
            DedValue= at.value().toDouble();
            break;
         default:
            break;
      }
   }

   return true;

}
