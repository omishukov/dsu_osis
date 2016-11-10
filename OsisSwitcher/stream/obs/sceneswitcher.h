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

class ObsSceneSwitcher : public QObject
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(QObject *parent = 0);
   ~ObsSceneSwitcher();

   void LoadActions(QString& inifile, SwitcherOsisIf* osisIf);
   QMap<int, ObsAction*>* GetActions() { return &ObsActions; }
   int GetRowCount() { return RowActionMap.size(); }
   int GetColumnCount() { return NUM_SCENES_PER_ACTION; }
   QStringList GetRow(int row);

signals:

public slots:
   void HandleEvent(int act);
   void Initialize();

private:
   void RemoveCompletesActions();

   QMap<QString, QList<int>>* SceneHkeyMap;
   QMap<QString, QList<int>>* TransitionHkeyMap;
   ObsAction* CurrentAction;
   QList<ObsAction*> ActiveActions;
   QMap<int, ObsAction*> ObsActions;
   QMap<int, int> RowActionMap;
   QString Inifile;

};

#endif // OBSSCENESWITCHER_H