#ifndef OBSOSISIF_H
#define OBSOSISIF_H

#include <QString>
#include <QMap>

class ObsOsisIf
{
public:
   virtual ~ObsOsisIf() {}

   virtual QString GetCurrentSkaterName() = 0;
   virtual bool GetSegmentStartList(QMap<int, QList<QString>>& segmentStartList) = 0;
};

#endif // OBSOSISIF_H
