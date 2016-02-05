#include <QDebug>
#include <QMetaEnum>
#include "prfranking.h"

OsisPrfRanking::OsisPrfRanking(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisPrfRanking::staticMetaObject, "Prf_Ranking")
{
   ProcessAttributes(osisElement);

}
