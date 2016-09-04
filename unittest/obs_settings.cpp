#include <osis_unittest.h>


void UnittestTest::ObsTransition()
{
   ObsSceneSwitcher* oss = new ObsSceneSwitcher(new Actions(), "C:/Users/olm/AppData/Roaming/obs-studio", 0);
   oss->LoadObsConfiguration();
   oss->ObsScenesList[0]->SwitchScene();
}

void UnittestTest::ObsParseTransitionIni()
{
//   ObsSceneSwitcher* oss = new ObsSceneSwitcher(new Actions(), "c:/Users/Oleksander/AppData/Roaming/obs-studio");
   ObsSceneSwitcher* oss = new ObsSceneSwitcher(new Actions(), "C:/Users/olm/AppData/Roaming/obs-studio", 0);
   oss->LoadObsConfiguration();
}
