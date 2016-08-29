#include "sceneswitcher.h"
#include <QSettings>
#include <QTableWidgetItem>

extern const QString inifile;

ObsSceneSwitcher::ObsSceneSwitcher(Actions* actions, QObject *parent)
   : QObject(parent)
   , osisAction(actions)
{
   osisAction->SetObsIf(this);
   LoadObsConfiguration();
   LoadActions();
}

ObsSceneSwitcher::~ObsSceneSwitcher()
{
   for (auto obsAction : ObsActions)
   {
      delete obsAction;
   }
   ObsActions.clear();
   delete tableModel;
}

void ObsSceneSwitcher::LoadObsConfiguration()
{

}

void ObsSceneSwitcher::LoadActions()
{
   QSettings settings(inifile, QSettings::IniFormat);

   for(int i = Actions::NO_ACTIONS + 1; i < Actions::LAST_ACTION; i++)
   {
      settings.beginGroup(osisAction->GetActionName(i));
      ObsAction* obsAction = new ObsAction(osisAction->GetActionName(i));
      obsAction->delay1 = settings.value("DELAY1", "0").toUInt();
      obsAction->delay2 = settings.value("DELAY2", "0").toUInt();
      obsAction->scene1 = settings.value("SCENE1", "").toString();
      obsAction->scene2 = settings.value("SCENE2", "").toString();
      settings.endGroup();
      obsAction->Validate();
      if (ObsActions.contains(i))
      {
         delete ObsActions[i];
      }
      ObsActions[i] = obsAction;
   }
}

void ObsSceneSwitcher::InitUi(QTableView* tableView)
{
   tableModel = new QStandardItemModel(ObsActions.count(), 5);
   tableView->setModel(tableModel);
   tableModel->setHorizontalHeaderLabels(QString("Event;Delay;Scene1;Delay;Scene2").split(";"));
   uint row = 0;
   for (auto obsAction : ObsActions)
   {
      QModelIndex index0 = tableModel->index(row, 0, QModelIndex());
      QModelIndex index1 = tableModel->index(row, 1, QModelIndex());
      QModelIndex index2 = tableModel->index(row, 2, QModelIndex());
      QModelIndex index3 = tableModel->index(row, 3, QModelIndex());
      QModelIndex index4 = tableModel->index(row, 4, QModelIndex());

      tableModel->setData(index0, QVariant(obsAction->actionName));
      tableModel->setData(index1, QVariant(obsAction->delay1));
      tableModel->setData(index2, QVariant(obsAction->scene1));
      tableModel->setData(index3, QVariant(obsAction->delay2));
      tableModel->setData(index4, QVariant(obsAction->scene2));

      row++;
   }
   tableView->resizeColumnsToContents();

   tableView->show();
}

void ObsSceneSwitcher::HandleEvent(int action)
{
   // Find action in SceneSwitch list
}

bool ObsAction::Validate()
{
   if (scene1.isEmpty())
   {
      delay1 = delay2 = 0;
      scene2.clear();
   }
   return false;
}
