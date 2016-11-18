#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QMetaEnum>
#include "actions.h"
#include "sceneinfo.h"
#include "scenetableui.h"
#include "osisif.h"
#include "streamif.h"

const int NUM_SCENES_PER_ACTION = 2;

class ObsSceneSwitcher : public QObject, public StreamIf
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(QString& inifile, OsisIf* osisIf, QObject *parent = 0);
   ~ObsSceneSwitcher();

   int GetRowCount() { return RowActionMap.size(); }
   int GetNumOfScenes() { return NUM_SCENES_PER_ACTION; }
   QStringList GetRow(int row);

   void Action(int action);
   QStringList GetScenes();
   QStringList GetTransitions();
   int GetNoOfActions();
   int GetNoOfSceneTransitions();
   void SetTransition(QString currentTransition);
   void SetDataLocker(QMutex* m);

signals:
   void NewAction(int);

public slots:
   void HandleEvent(int act);
   void Initialize();

private:
   void LoadActions(QString& inifile, OsisIf* osisIf);

   QMap<QString, QList<int>>* SceneHkeyMap;
   QMap<QString, QList<int>>* TransitionHkeyMap;
   ObsAction* CurrentAction;
   QList<ObsAction*> ActiveActions;
   QMap<int, ObsAction*> ObsActions;
   QMap<int, int> RowActionMap;
   QString Inifile;
   ObsScenes Obs;
};

#endif // OBSSCENESWITCHER_H
