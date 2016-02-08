#include <QDebug>
#include <QMetaEnum>
#include "action.h"

OsisAction::OsisAction(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisAction::staticMetaObject, "Action")
{
   ProcessAttributes(osisElement);
}
