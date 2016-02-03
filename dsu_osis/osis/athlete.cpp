#include <QDebug>
#include <QMetaEnum>
#include "athlete.h"

OsisAthlete::OsisAthlete(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisAthlete::staticMetaObject, "Athlete")
{
   ProcessAttributes(osisElement);

   bool ok;
   Id = GetAttribute(OsisAthlete::ID).toInt(&ok);
   if (!ok)
   {
      Id = -1;
      qCritical() << "Invalid Athlete ID: " << GetAttribute(OsisAthlete::ID) << ", Name:" << GetAttribute(OsisAthlete::Full_Name) << endl;
   }

}
