#ifndef OBSSCENESWITCHER_H
#define OBSSCENESWITCHER_H

#include <QObject>
#include "actions.h"

class ObsSceneSwitcher : public QObject
{
   Q_OBJECT
public:
   explicit ObsSceneSwitcher(Actions* actions, QObject *parent = 0);

signals:

public slots:

private:
   Actions* osisAction;
};

#endif // OBSSCENESWITCHER_H
