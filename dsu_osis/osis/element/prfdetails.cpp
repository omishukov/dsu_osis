#include <QDebug>
#include <QMetaEnum>
#include "prfdetails.h"

OsisPrfDetails::OsisPrfDetails(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisPrfDetails::staticMetaObject, "PrfDetails")
{
   ProcessAttributes(osisElement);
}
