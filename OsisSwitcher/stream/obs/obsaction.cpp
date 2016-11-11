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

ObsAction::ObsAction(QString& actionName, QMap<QString, int>& sceneDelay, OsisIf* osisIf, QObject* parent)
   : QObject(parent)
   , ActionName(actionName)
{

}

ObsAction::~ObsAction()
{
   Scene.Cancel();
}

void ObsAction::Execute()
{
   Scene.SwitchScene();
}

bool ObsAction::Completed()
{
   return Scene.Completed();
}

QStringList ObsAction::GetTableRow()
{
   QStringList row;
   row << ActionName;
   for(auto scene : SceneDelayMap->keys())
   {
      row << QString::number(SceneDelayMap.value(scene)) << scene;
   }
   return row;
}

void ObsAction::SceneCompleted()
{

}
