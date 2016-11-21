#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QMetaEnum>
#include "actions.h"
#include "obsscenes.h"
#include "scenetableui.h"
#include "osisif.h"
#include "streamif.h"
#include "obsaction.h"


class ObsSceneSwitcher : public QObject, public StreamIf
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(QString& inifile, OsisIf* osisIf, QObject *parent = 0);
   ~ObsSceneSwitcher();

   void Action(int action);
   QStringList GetScenes();
   QStringList GetTransitions();
   void SetTransition(QString currentTransition);
   void SetDataLocker(QMutex* m);

signals:
   void NewAction(int);

public slots:
   void HandleEvent(int act);
   void Initialize();

private:
   QMap<QString, QList<int>>* SceneHkeyMap;
   QMap<QString, QList<int>>* TransitionHkeyMap;
   ObsAction* CurrentAction;
   QList<ObsAction*> ActiveActions;
   QMap<int, ObsAction*> ObsActions;
   QString Inifile;
   ObsScenes Obs;
};

#endif // OBSSCENESWITCHER_H
