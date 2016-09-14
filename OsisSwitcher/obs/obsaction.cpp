#include "obsaction.h"

ObsAction::ObsAction(ActionToScene *action, ObsAction *previousAction, QObject* parent)
   : QObject(parent)
   , ActionName(action->ActionName)
   , Scene(action->Scene, action->Hkey, action->Delay)
   , NextScene(action->NextScene, action->NextHkey, action->NextDelay)
   , Transition(action->Transition, action->TransitionHkey, 0)
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
