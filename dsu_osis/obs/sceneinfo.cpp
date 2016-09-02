#include <windows.h>
#include "sceneinfo.h"

SceneInfo::SceneInfo(QString name, QList<int> list, QObject *parent)
   : QObject(parent)
   , SceneName(name)
   , Hotkeys(list)
   , Transition(0)
   , NextScene(0)
   , PreviousScene(0)
   , Delay(0)
   , TimerId(0)
{
   timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), this, SLOT(TimerExpired()));
}

SceneInfo::~SceneInfo()
{
   if (TimerId > 0)
   {
      killTimer(TimerId);
   }
}

void SceneInfo::TimerExpired()
{
   qInfo() << "Timeout";

}

void SceneInfo::SwitchScene(SceneInfo *previousScene)
{
   if (Hotkeys.isEmpty())
   {
      return;
   }
   PreviousScene = previousScene;

   if (TimerId > 0)
   {
      killTimer(TimerId);
      TimerId = 0;
   }

   timer->start(1000);
   if (Delay > 0)
   {
//      TimerId = startTimer(Delay*1000);
//      timer->start(1000);

   }
   else
   {
      SendHotkey();
   }
}

void SceneInfo::SetTransition(SceneInfo* transition)
{
   Transition = transition;
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
      PreviousScene = 0;
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
}

void SceneInfo::Cancel()
{
   if (TimerId > 0)
   {
      killTimer(TimerId);
      TimerId = 0;
   }
   if (NextScene)
   {
      NextScene->Cancel();
   }

}

//void SceneInfo::timerEvent(QTimerEvent* event)
//{
//   killTimer(TimerId);
//   TimerId = 0;
//   SendHotkey();
//}
