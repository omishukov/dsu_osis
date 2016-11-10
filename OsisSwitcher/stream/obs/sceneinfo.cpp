#include <windows.h>
#include "sceneinfo.h"

SceneInfo::SceneInfo(QString name, QList<int> hKey, int delay, QObject *parent)
   : QObject(parent)
   , SceneName(name)
   , Hotkeys(hKey)
   , Transition(0)
   , NextScene(0)
   , PreviousScene(0)
   , Delay(delay)
   , ActionCompleted(false)
{
   Timer.setSingleShot(true);
   connect(&Timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
   CurrentScene = SceneDelay.begin();
}

SceneInfo::~SceneInfo()
{
   ActionCompleted = true;
   if (NextScene)
   {
      NextScene->Cancel();
   }
   Timer.stop();
}

void SceneInfo::TimerExpired()
{
   qInfo() << "Timeout";
   SendHotkey();
}

void SceneInfo::SwitchScene()
{
   if (Hotkeys.isEmpty())
   {
      ActionCompleted = true;
      return;
   }

   if (PreviousScene)
   {
      PreviousScene->Cancel();
   }

   if (Delay > 0)
   {
      Timer.start(Delay*1000);

   }
   else
   {
      SendHotkey();
   }
}

void SceneInfo::SetTransition(SceneInfo* transition)
{
   if (!transition)
   {
      return;
   }
   Transition = transition;
   if (NextScene)
   {
      NextScene->SetTransition(transition);
   }
}

void SceneInfo::SetNextScene(SceneInfo* nextScene)
{
    NextScene = nextScene;
}

void SceneInfo::SendHotkey()
{
   if (PreviousScene)
   {
      PreviousScene->Cancel();
   }

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
   Sleep(100);
   // Release the keys in reverse order
   it--;
   for ( ; it != Hotkeys.constBegin(); --it )
   {
       ip.ki.wVk = static_cast<uint16_t>(*it);
       ip.ki.dwFlags = KEYEVENTF_KEYUP;
       SendInput(1, &ip, sizeof(INPUT));
   }
   ip.ki.wVk = static_cast<uint16_t>(*it);
   ip.ki.dwFlags = KEYEVENTF_KEYUP;
   SendInput(1, &ip, sizeof(INPUT));
   Sleep(100);

   if (Transition)
   {
      Transition->SwitchScene();
   }

   if (NextScene)
   {
      NextScene->SwitchScene();
   }
   ActionCompleted = true;
}

void SceneInfo::Cancel()
{
   Timer.stop();

   if (NextScene)
   {
      NextScene->Cancel();
   }

   if (PreviousScene)
   {
      PreviousScene->Cancel();
   }
   ActionCompleted = true;
}

bool SceneInfo::Completed()
{
   if (ActionCompleted && (!NextScene || NextScene->Completed()))
   {
      return true;
   }
   return false;
}
