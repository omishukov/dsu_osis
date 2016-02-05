#include <QDebug>
#include <QMetaEnum>
#include "warmupgroup.h"

OsisWarmupGroup::OsisWarmupGroup(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisWarmupGroup::staticMetaObject, "Warmup_Group")
{
   ProcessAttributes(osisElement);

   bool ok;
   Ind = GetAttribute(OsisWarmupGroup::Index).toInt(&ok);
   if (!ok)
   {
      Ind = -1;
      qCritical() << "Invalid Element Index: " << GetAttribute(OsisWarmupGroup::Index) << ", Number:" << GetAttribute(OsisWarmupGroup::Number) << endl;
   }
}
