#ifndef OBSACTION_H
#define OBSACTION_H

#include <QMetaEnum>
#include <QObject>
#include "sceneinfo.h"

class ObsAction : public QObject
{
   Q_OBJECT
public:
   ObsAction(QString name, QObject *parent = 0);
   ~ObsAction();

   QString actionName;

public:
   void Execute(ObsAction* previousAction);

   void SetScene1(SceneInfo* sceneInfo);
   QString GetScene1Name();

   void SetScene2(SceneInfo* sceneInfo);
   QString GetScene2Name();

   void SetDelay1(int delay);
   int GetDelay1();

   void SetDelay2(int delay);
   int GetDelay2();

   void SetTransition(SceneInfo* transition);
   QString GetTransitionName();

   SceneInfo* GetScene() { return Scene;}

public slots:
   void TimerExpired();

private:
   SceneInfo* Scene;
   SceneInfo* Transition;
   int Delay1;
   int Delay2;
   QTimer* timer;
};

#endif // OBSACTION_H
