#include "obsaction.h"

ObsAction::ObsAction(Action2SceneStruct& actionInfo, ObsAction *previousAction, QObject* parent)
   : QObject(parent)
   , ActionName(actionInfo.ActionName)
   , Scene(actionInfo.Scene, actionInfo.Hkey, actionInfo.Delay)
   , NextScene(actionInfo.NextScene, actionInfo.NextHkey, actionInfo.NextDelay)
   , Transition(actionInfo.Transition, actionInfo.TransitionHkey, 0)
{
   Scene.SetNextScene(&NextScene);
   Scene.SetTransition(&Transition);
   if (previousAction)
   {
      Scene.SetPreviousScene(previousAction->GetScene());
   }
}

ObsAction::~ObsAction()
{
   Scene.Cancel();
}

void ObsAction::Execute()
{
   Scene.SwitchScene();
}
