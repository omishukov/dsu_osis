#include "obsaction.h"

ObsAction::ObsAction(QString name, QObject* parent)
   : QObject(parent)
   , actionName(name)
   , Scene(new SceneInfo(this))
   , Transition(0)
   , Delay1(0)
   , Delay2(0)
{
   Scene->SetNextScene(new SceneInfo(this));
   Scene->SetTransition(new SceneInfo(this));
}

ObsAction::~ObsAction()
{
   delete Scene->GetNextScene();
   delete Scene->GetTransition();
   delete Scene;
}

void ObsAction::Execute(ObsAction* previousAction)
{
   Scene->SwitchScene(previousAction?previousAction->GetScene():0);
}

void ObsAction::SetScene1(SceneInfo* sceneInfo)
{
   if (!sceneInfo ||
       !QString::compare(Scene->SceneName, sceneInfo->SceneName))
   {
      return;
   }
   Scene->Update(sceneInfo);
}

QString ObsAction::GetScene1Name()
{
   return Scene->SceneName;
}

void ObsAction::SetScene2(SceneInfo* sceneInfo)
{
   if (sceneInfo)
   {
      Scene->GetNextScene()->Update(sceneInfo);
   }
}

QString ObsAction::GetScene2Name()
{
   return Scene->GetNextScene()->SceneName;
}

void ObsAction::SetDelay1(int delay)
{
   Scene->SetDelay(delay);
   Delay1 = delay;
}

int ObsAction::GetDelay1()
{
   return Scene->GetDelay();
}

void ObsAction::SetDelay2(int delay)
{
   Scene->GetNextScene()->SetDelay(delay);
   Delay2 = delay;
}

int ObsAction::GetDelay2()
{
   return Scene->GetNextScene()->GetDelay();
}

void ObsAction::SetTransition(SceneInfo* transition)
{
   Transition = new SceneInfo(transition->SceneName, transition->Hotkeys);
   Scene->GetTransition()->Update(transition);
   if (Scene->GetNextScene())
   {
      Scene->GetNextScene()->GetTransition()->Update(transition);
   }
}

QString ObsAction::GetTransitionName()
{
   return Scene->GetTransition()->SceneName;
}

void ObsAction::TimerExpired()
{
   qInfo() << "Timeout()";
}
