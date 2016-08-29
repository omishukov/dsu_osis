#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include "actions.h"

class ObsAction
{
public:
   ObsAction(QString name) :delay1(0),delay2(0), actionName(name) {}

   uint delay1;
   uint delay2;
   QString scene1;
   QString scene2;
   QString actionName;

public:
   bool Validate();
};

class ObsSceneSwitcher : public QObject
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(Actions* actions, QObject *parent = 0);
   ~ObsSceneSwitcher();

   void LoadObsConfiguration();
   void LoadActions();
   void InitUi(QTableView* tableView);


signals:

public slots:
   void HandleEvent(int action);

private:
   Actions* osisAction;
   QMap<uint, ObsAction*> ObsActions;
   QStandardItemModel* tableModel;
};

#endif // OBSSCENESWITCHER_H
