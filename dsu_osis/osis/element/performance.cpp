#include <QDebug>
#include <QMetaEnum>
#include "performance.h"

OsisPerformance::OsisPerformance(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisPerformance::staticMetaObject, "Performance")
{
   ProcessAttributes(osisElement);

   bool ok;
   Id = GetAttribute(OsisPerformance::ID).toInt(&ok);
   if (!ok)
   {
      Id = -1;
      qCritical() << "Invalid Performance ID: " << GetAttribute(OsisPerformance::ID) << endl;
   }

}

void OsisPerformance::AddElement(OsisElement* newElement)
{
   if (newElement && newElement->GetIndex() != -1)
   {
      int Ind = newElement->GetIndex();
      if (Elements.contains(Ind))
      {
         Elements.value(Ind)->Update(*newElement);
         delete newElement;
      }
      else
      {
         Elements.insert(Ind, newElement);
      }
   }
}
