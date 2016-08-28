#include "sceneswitcher.h"
#include <QSettings>

extern const QString inifile;

ObsSceneSwitcher::ObsSceneSwitcher(Actions* actions, QObject *parent)
   : QObject(parent)
   , osisAction(actions)
{
   osisAction->SetObsIf(this);

   QSettings settings(inifile, QSettings::IniFormat);

   for(int i = Actions::NO_ACTIONS + 1; i < Actions::LAST_ACTION; i++)
   {
      settings.beginGroup(osisAction->GetActionName(i));
      ObsAction* obsAction = new ObsAction();
      obsAction->delay1 = settings.value("DELAY1", "0").toUInt();
      obsAction->delay2 = settings.value("DELAY2", "0").toUInt();
      obsAction->scene1 = settings.value("SCENE1", "").toString();
      obsAction->scene2 = settings.value("SCENE2", "").toString();
      if (obsAction->Validate())
      {
         ObsActions[i] = obsAction;
      }
      else
      {
         delete obsAction;
      }
   }
//   ConnectionType = ConnectAs(settings.value("mode", SERVER).toInt());
//   IpAddress = settings.value("address", "127.0.0.1").toString();
//   IpPort = settings.value("port", "0").toString();
//   settings.endGroup();

}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
   for (auto obsAction : ObsActions)
   {
      delete obsAction;
   }
   ObsActions.clear();
}

void ObsSceneSwitcher::HandleEvent(int action)
{
   // Find action in SceneSwitch list
}

bool ObsAction::Validate()
{
   return false;
}
