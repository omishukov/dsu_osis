#include <windows.h>
#include "sceneinfo.h"

SceneInfo::SceneInfo(QString name, QList<int> list)
   : SceneName(name)
   , Hotkeys(list)
{

}

void SceneInfo::SwitchScene()
{
   INPUT ip;
   ip.type = INPUT_KEYBOARD;
   ip.ki.wScan = 0;
   ip.ki.time = 0;
   ip.ki.dwExtraInfo = 0;

   // Press keys
   QList<int>::ConstIterator it = Hotkeys.constBegin();
   for ( ; it != Hotkeys.constEnd(); ++it )
   {
       // Press the "Ctrl" key
       ip.ki.wVk = static_cast<uint16_t>(*it);
       ip.ki.dwFlags = 0; // 0 for key press
       SendInput(1, &ip, sizeof(INPUT));
   }

   // Release the keys in reverse order
   it--;
   for ( ; it != Hotkeys.constBegin(); --it )
   {
       ip.ki.wVk = static_cast<uint16_t>(*it);
       ip.ki.dwFlags = KEYEVENTF_KEYUP;
       SendInput(1, &ip, sizeof(INPUT));
   }

}
