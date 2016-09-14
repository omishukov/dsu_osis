#ifndef OBSACTION_H
#define OBSACTION_H

#include <QMetaEnum>
#include <QObject>
#include "sceneinfo.h"

struct ActionToScene
{
   QString ActionName;
   int Delay;
   QString Scene;
   QList<int> Hkey;
   int NextDelay;
   QString NextScene;
   QList<int> NextHkey;
   QString Transition;
   QList<int> TransitionHkey;

};

class ObsAction : public QObject
{
   Q_OBJECT
public:
   ObsAction(ActionToScene *action, ObsAction* previousAction, QObject *parent = 0);
   ~ObsAction();

public:
   void Execute();
   SceneInfo* GetScene() { return &Scene;}

public slots:

private:
   QString ActionName;
   SceneInfo Scene;
   SceneInfo NextScene;
   SceneInfo Transition;
};

#endif // OBSACTION_H
