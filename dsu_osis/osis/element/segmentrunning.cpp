#include <QDebug>
#include <QMetaEnum>
#include "segmentrunning.h"

OsisSegmentRunning::OsisSegmentRunning(QDomElement& osisElement, QObject *parent)
   : QObject(parent)
   , OsisData(OsisSegmentRunning::staticMetaObject, "Segment_Running")
{
   ProcessAttributes(osisElement);

}
