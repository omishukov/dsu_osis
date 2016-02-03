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
