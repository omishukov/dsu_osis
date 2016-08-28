#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include "actions.h"

class ObsAction
{
public:
   ObsAction() :delay1(0),delay2(0) {}
   uint delay1;
   uint delay2;
   QString scene1;
   QString scene2;

public:
   bool Validate();
};

class ObsSceneSwitcher : public QObject
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(Actions* actions, QObject *parent = 0);
   ~ObsSceneSwitcher();

signals:

public slots:
   void HandleEvent(int action);

private:
   Actions* osisAction;
   QList<ObsAction*> ObsActions;
};

#endif // OBSSCENESWITCHER_H
