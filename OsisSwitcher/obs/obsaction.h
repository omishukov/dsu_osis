#ifndef OBSACTION_H
#define OBSACTION_H

#include <QMetaEnum>
#include <QObject>
#include "sceneinfo.h"
#include "scenedata.h"
#include "osisif.h"

class ObsAction : public QObject
{
   Q_OBJECT
public:
//   ObsAction(Action2SceneStruct& actionInfo, ObsAction* previousAction, QObject *parent = 0);
   ObsAction(QString &actionName, QMap<QString, int>& sceneDelay, SwitcherOsisIf* osisIf, QObject *parent = 0);
   ~ObsAction();

public:
   void Execute(ObsAction *previousAction = 0, int nextAction = -1);
//   SceneInfo* GetScene() { return &Scene;}
   bool Completed();
   bool Executable();
   QMap<QString, int>* GetSceneDelays() { return &SceneDelayMap; }
   QStringList GetTableRow();

public slots:
   void SceneCompleted();

private:
   QString ActionName;
//   SceneInfo Scene;
//   SceneInfo NextScene;
//   SceneInfo Transition;
   QMap<QString, int> SceneDelayMap;
   SwitcherOsisIf* OsisIf;
   bool Repeat;
   SceneData* ObsSceneFiles;
};

#endif // OBSACTION_H
