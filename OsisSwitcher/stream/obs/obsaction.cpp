#include "obsaction.h"

//ObsAction::ObsAction(Action2SceneStruct& actionInfo, ObsAction *previousAction, QObject* parent)
//   : QObject(parent)
//   , ActionName(actionInfo.ActionName)
//   , Scene(actionInfo.Scene, actionInfo.Hkey, actionInfo.Delay)
//   , NextScene(actionInfo.NextScene, actionInfo.NextHkey, actionInfo.NextDelay)
//   , Transition(actionInfo.Transition, actionInfo.TransitionHkey, 0)
//{
//   Scene.SetNextScene(&NextScene);
//   Scene.SetTransition(&Transition);
//   if (previousAction)
//   {
//      Scene.SetPreviousScene(previousAction->GetScene());
//   }
//   connect(&Scene, SIGNAL(ActionDone()), this, SLOT(SceneCompleted()));
//}

ObsAction::ObsAction(int action, OsisIf* osisIf, QObject* parent)
   : QObject(parent)
   , ActionName(osisIf->GetActionName(action))
{
   osisIf->GetActionName(action);

}

ObsAction::~ObsAction()
{
//   Scene.Cancel();
}

void ObsAction::Execute(ObsAction *previousAction, int nextAction)
{
   //   Scene.SwitchScene();
}

void ObsAction::SetScene(int sceneIndex, QString &scene)
{
   if (SceneDelayMap.contains(sceneIndex))
   {
      SceneDelayMap[sceneIndex].Scene = scene;
   }
   else
   {
      SceneDelayStruct newScene;
      newScene.Scene = scene;
      newScene.Delay = 0;
      SceneDelayMap.insert(sceneIndex, newScene);
   }

}

void ObsAction::SetDelay(int sceneIndex, int delay)
{

}

//bool ObsAction::Completed()
//{
//   return Scene.Completed();
//}


void ObsAction::SceneCompleted()
{

}
