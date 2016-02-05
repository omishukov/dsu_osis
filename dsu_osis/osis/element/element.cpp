#include <QDebug>
#include <QMetaEnum>
#include "element.h"

OsisElement::OsisElement(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisElement::staticMetaObject, "Element")
{
   ProcessAttributes(osisElement);

   bool ok;
   Ind = GetAttribute(OsisElement::Index).toInt(&ok);
   if (!ok)
   {
      Ind = -1;
      qCritical() << "Invalid Element Index: " << GetAttribute(OsisElement::Index) << ", Name:" << GetAttribute(OsisElement::Elm_Name) << endl;
   }
}
