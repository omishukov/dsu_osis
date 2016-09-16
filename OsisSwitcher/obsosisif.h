#ifndef OBSOSISIF_H
#define OBSOSISIF_H

#include <QString>
#include <QMap>

class ObsOsisIf
{
public:
   virtual ~ObsOsisIf() {}

   virtual QString GetCurrentSkaterName() = 0;
   virtual QString GetCurrentSkaterNumber() = 0;
   virtual QString GetCurrentSkaterNation() = 0;
   virtual QString GetCurrentSkaterClub() = 0;
   virtual QString GetEventName() = 0;
   virtual QString GetSegmentName() = 0;
   virtual QString GetCategoryName() = 0;
   virtual QString GetPoints() = 0;
   virtual QString GetTES() = 0;
   virtual QString GetTCS() = 0;
   virtual QString GetBonus() = 0;
   virtual QString GetDeduction() = 0;
   virtual QString GetRank() = 0;
   virtual QString GetCurrentWarmUpGroupNumber() = 0;
   virtual bool GetSegmentStartList(QMap<int, QList<QString>>& segmentStartList) = 0;
   virtual bool GetSegmentResultList(QMap<int, QList<QString>>& segmentResultList) = 0;
   virtual bool GetWarmUpStartList(QMap<int, QList<QString>>& warmUpStartList) = 0;
   virtual void GetWarmUpGroupsList(QList<int>& WarmUpList) = 0;
};

#endif // OBSOSISIF_H
