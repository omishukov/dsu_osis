#ifndef OBSACTION_H
#define OBSACTION_H

#include <QMetaEnum>
#include <QObject>
#include "sceneinfo.h"
#include "actiontoscene.h"

class ObsAction : public QObject
{
   Q_OBJECT
public:
   ObsAction(Action2SceneStruct& actionInfo, ObsAction* previousAction, QObject *parent = 0);
   ~ObsAction();

public:
   void Execute();
   SceneInfo* GetScene() { return &Scene;}
   bool Completed();

public slots:
   void SceneCompleted();

private:
   QString ActionName;
   SceneInfo Scene;
   SceneInfo NextScene;
   SceneInfo Transition;
};

#endif // OBSACTION_H
