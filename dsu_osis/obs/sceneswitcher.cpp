#include "sceneswitcher.h"

ObsSceneSwitcher::ObsSceneSwitcher(Actions* actions, QObject *parent)
   : QObject(parent)
   , osisAction(actions)
{

}
