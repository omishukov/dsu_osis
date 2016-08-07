#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>

class Actions
{
public:
   enum ObsAction
   {
      SCHEDULE_LIST,
      START_LIST,
      WARMUP_LIST
   };

public:
   Actions();
};

#endif // ACTIONS_H
