#include "obsaction.h"

ObsAction::ObsAction(QString name, QObject* parent)
   : QObject(parent)
   , actionName(name)
   , Scene(0)
   , Transition(0)
   , Delay1(0)
   , Delay2(0)
{
//   timer = new QTimer(this);
//   connect(timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
//   timer->start(1000);
}

ObsAction::~ObsAction()
{
   if (Scene)
   {
      delete Scene->GetNextScene();
      delete Scene->GetTransition();
   }
   delete Scene;
}

void ObsAction::Execute(ObsAction* previousAction)
{
   if (!Scene)
   {
      return;
   }
   Scene->SwitchScene(previousAction?previousAction->GetScene():0);
}

void ObsAction::SetScene1(SceneInfo* sceneInfo)
{
   SceneInfo* nextScene = 0;
   SceneInfo* transition = Transition;
   if (Scene)
   {
      if (!sceneInfo)
      {
         delete Scene->GetNextScene();
         Transition = Scene->GetTransition();
         delete Scene;
         Scene = 0;
         return;
      }
      if (!QString::compare(Scene->SceneName, sceneInfo->SceneName))
      {
         return;
      }
      nextScene = Scene->GetNextScene();
      transition = Scene->GetTransition();
      delete Scene;
   }
   Scene = new SceneInfo(sceneInfo->SceneName, sceneInfo->Hotkeys);
   Scene->SetDelay(Delay1);
   Scene->SetNextScene(nextScene);
   Scene->SetTransition(transition);
   Transition = transition;
}

QString ObsAction::GetScene1Name()
{
   if (Scene)
   {
      return Scene->SceneName;
   }
   return QString();
}

void ObsAction::SetScene2(SceneInfo* sceneInfo)
{
   if (Scene)
   {
      delete Scene->GetNextScene();
      Scene->SetNextScene(0);
      if (sceneInfo)
      {
         Scene->SetNextScene(new SceneInfo(sceneInfo->SceneName, sceneInfo->Hotkeys));
         Scene->GetNextScene()->SetDelay(Delay2);
      }
   }
}

QString ObsAction::GetScene2Name()
{
   if (Scene)
   {
      SceneInfo* nextScene = Scene->GetNextScene();
      if (nextScene)
      {
         return nextScene->SceneName;
      }
   }
   return QString();
}

void ObsAction::SetDelay1(int delay)
{
   if (Scene)
   {
      Scene->SetDelay(delay);
   }
   Delay1 = delay;
}

int ObsAction::GetDelay1()
{
   return Scene?Scene->GetDelay():0;
}

void ObsAction::SetDelay2(int delay)
{
   if (Scene)
   {
      SceneInfo* nextScene = Scene->GetNextScene();
      if (nextScene)
      {
         nextScene->SetDelay(delay);
      }
   }
   Delay2 = delay;
}

int ObsAction::GetDelay2()
{
   if (Scene)
   {
      SceneInfo* nextScene = Scene->GetNextScene();
      if (nextScene)
      {
         return nextScene->GetDelay();
      }
   }
   return 0;
}

void ObsAction::SetTransition(SceneInfo* transition)
{
   if (Scene)
   {
      delete Scene->GetTransition();
      Scene->SetTransition(0);
      Transition = transition;
      if (transition)
      {
         Scene->SetTransition(new SceneInfo(transition->SceneName, transition->Hotkeys));
      }
   }
}

QString ObsAction::GetTransitionName()
{
   if (Scene)
   {
      SceneInfo* transition = Scene->GetTransition();
      if (transition)
      {
         return transition->SceneName;
      }
   }
   return QString();
}

void ObsAction::TimerExpired()
{
   qInfo() << "Timeout()";
}

