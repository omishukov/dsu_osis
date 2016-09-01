#ifndef OBSACTION_H
#define OBSACTION_H

#include <QObject>

class ObsAction
{
public:
   ObsAction(QString name) :delay1(0),delay2(0), actionName(name) {}

   int delay1;
   int delay2;
   QString scene1;
   QString scene2;
   QString transition;
   QString actionName;

public:
   bool Validate();
};

#endif // OBSACTION_H
