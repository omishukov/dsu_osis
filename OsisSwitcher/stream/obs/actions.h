#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <QList>
#include <QMetaEnum>
#include <QMutex>
#include <osisif.h>
#include "actiontoscene.h"

class Actions : public QObject
{
   Q_OBJECT

public:
   Actions(ActionToScene* actionInfo, QObject *parent = 0);

   inline void SetOsisInfoIf(OsisIf* obsOsisIf) { OsisDataIf = obsOsisIf; }

   void SetLock(QMutex* m) {M = m;}

public slots:
   void AddAction(int action);
   void DoActions(int action);

signals:
   void SendOsisEvent(int);

private:
   void SaveToFile(const QString& file, QString text);
   void GenerateHtml(const QString& fileName, QMap<int, QList<QString> >& outputList);
   void GenerateHtml(const QString& fileName, const QString& text);
   void GenerateSegmentResultListHtml(QMap<int, QList<QString>>& segmentResultList);
   void GenerateWarmUpStartListHtml(QMap<int, QList<QString>>& warmUpGroupNameList);

private:
   QList<int> ActionList;
   OsisIf* OsisDataIf;
   QMutex* M;
   ActionToScene* ActionInfo;
   QList<int> WarmUpList;
};

#endif // ACTIONS_H
