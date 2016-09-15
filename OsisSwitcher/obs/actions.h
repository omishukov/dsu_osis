#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <QList>
#include <QMetaEnum>
#include <QMutex>
#include <obsosisif.h>
#include "actiontoscene.h"

class Actions : public QObject
{
   Q_OBJECT

public:
   Actions(ActionToScene* actionInfo, QObject *parent = 0);

   inline void SetOsisInfoIf(ObsOsisIf* obsOsisIf) { OsisIf = obsOsisIf; }

   void SetLock(QMutex* m) {M = m;}

public slots:
   void AddAction(int action);
   void DoActions();

signals:
   void SendOsisEvent(int);

private:
   void SaveToFile(const QString& file, QString text);
   void GenerateHtml(QMap<int, QList<QString>>& segmentStartList);
   void GenerateSegmentResultListHtml(QMap<int, QList<QString>>& segmentResultList);

private:
   QList<int> ActionList;
   ObsOsisIf* OsisIf;
   QMutex* M;
   ActionToScene* ActionInfo;
};

#endif // ACTIONS_H
