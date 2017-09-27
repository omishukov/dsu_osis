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
   void GenerateHtml(const QString& fileName, QMap<int, QList<QString> >& outputList);
   void GenerateNewHtmlList(const QString& fileName, QMap<int, QList<QString> >& outputList, const QString &headLine);
   void GenerateHtml(const QString& fileName, const QString& text);
   void GenerateEventInfoHtml(const QString& fileName);
   void GenerateSkaterInfoHtml(const QString& fileName);
   void GenerateResultHtml(const QString& fileName);
   void GenerateSegmentResultListHtml(QMap<int, QList<QString>>& segmentResultList);
   void GenerateWarmUpStartListHtml(QMap<int, QList<QString>>& warmUpGroupNameList);

private:
   QList<int> ActionList;
   ObsOsisIf* OsisIf;
   QMutex* M;
   ActionToScene* ActionInfo;
   QList<int> WarmUpList;
};

#endif // ACTIONS_H
