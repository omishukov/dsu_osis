#ifndef ACTIONTOSCENE_H
#define ACTIONTOSCENE_H

#include <QObject>
#include <QJsonArray>
#include <QMetaEnum>

struct Action2SceneStruct
{
   QString ActionName;
   int Delay;
   QString Scene;
   QList<int> Hkey;
   int NextDelay;
   QString NextScene;
   QList<int> NextHkey;
   QString Transition;
   QList<int> TransitionHkey;

};

class ActionToScene : public QObject
{
   Q_OBJECT
public:
   explicit ActionToScene(QObject *parent = 0);

   void LoadSceneConfiguration(QString obsconfig);
   void LoadActionConfiguration(QString& inifile);
   QString GetActionName(int action);
   Action2SceneStruct GetActionSceneInfo(int action);
   QList<QString> GetSceneList();
   QList<QString> GetTransitionList();
   void UpdateAction(int action, Action2SceneStruct& actionInfo);

   enum OsisActionCommand
   {
      NO_ACTIONS,
      ACTION_1SC, // Send Technical Element score Note: A message with 1SC action code is sent after the calculation of a performance result.
                  // Due to the big size of the message, it was split into several messages.
                  // Instead of one message with 1SC action code a sequence of 6 messages is sent in the following order: 1S1, 1S2, 1S3, 1S4, (1S5,) 1SC.
//      ACTION_1S1, // Result of current performance
//      ACTION_1S2, // Segment ranking
//      ACTION_1S3, // Category standing
//      ACTION_1S4, // Remaining start list
//      ACTION_1S5, // Team Standing
//      ACTION_2SC, // Send Program Components score
//      ACTION_3SC, // Send total score
      ACTION_CLR, // Clear scoreboard
      ACTION_ELM, // Executed elements of current performer
      ACTION_ELS, // Live calculation of current Skater
      ACTION_INI, // Initialise
      ACTION_IDT, // Send logo
      ACTION_IRS, // Send intermediate result
      ACTION_JDG, // Send judge
      ACTION_LTV, // Live Technical Element Score (TES)
      ACTION_NAM, // send name of active performer
      ACTION_NXP, // send next page (result or start list page)
      ACTION_RES, // Send result
      ACTION_SEG, // Send segment name
      ACTION_STL, // Send start list
      ACTION_STP, // Stop
      ACTION_NXT, // Next performer
      ACTION_PRV, // Previous performer
      ACTION_TBW, // Time count backward
      ACTION_TFW, // Time count forward
      ACTION_TR1, // Overall team standing
      ACTION_TR2, // Overall team standing
      ACTION_TST, // Time stopped
      ACTION_TPA, // Time pause
      ACTION_TCL, // Clear time
      ACTION_TIM, // Time value
      ACTION_URK, // Ranking Update
      ACTION_VTR, // Victory Ceremony
      ACTION_WUP, // send warm up group

      LAST_ACTION
   };
   Q_ENUM(OsisActionCommand)

signals:

public slots:

private:
   QString ReadObsConfiguration(QString& sceneFile);
   QList<int> GetHotkeys(QJsonArray& jHotkeyArray);
   int GetVirtualKey(int key);
   void SaveSceneConfiguration();

   Action2SceneStruct ActionToScenes[LAST_ACTION];
   QMetaEnum MetaObsKeyEnum;
   QMetaEnum MetaActionsEnum;
   QMap<QString, QList<int>> SceneHkeyMap;
   QMap<QString, QList<int>> TransitionHkeyMap;
   QString Inifile;

public:
   enum obs_key {
      OBS_KEY_RETURN,
      OBS_KEY_ESCAPE,
      OBS_KEY_TAB,
      OBS_KEY_BACKTAB,
      OBS_KEY_BACKSPACE,
      OBS_KEY_INSERT,
      OBS_KEY_DELETE,
      OBS_KEY_PAUSE,
      OBS_KEY_PRINT,
      OBS_KEY_CLEAR,
      OBS_KEY_HOME,
      OBS_KEY_END,
      OBS_KEY_LEFT,
      OBS_KEY_UP,
      OBS_KEY_RIGHT,
      OBS_KEY_DOWN,
      OBS_KEY_PAGEUP,
      OBS_KEY_PAGEDOWN,
      OBS_KEY_SHIFT,
      OBS_KEY_CONTROL,
      OBS_KEY_ALT,
      OBS_KEY_CAPSLOCK,
      OBS_KEY_NUMLOCK,
      OBS_KEY_SCROLLLOCK,
      OBS_KEY_F1,
      OBS_KEY_F2,
      OBS_KEY_F3,
      OBS_KEY_F4,
      OBS_KEY_F5,
      OBS_KEY_F6,
      OBS_KEY_F7,
      OBS_KEY_F8,
      OBS_KEY_F9,
      OBS_KEY_F10,
      OBS_KEY_F11,
      OBS_KEY_F12,
      OBS_KEY_F13,
      OBS_KEY_F14,
      OBS_KEY_F15,
      OBS_KEY_F16,
      OBS_KEY_F17,
      OBS_KEY_F18,
      OBS_KEY_F19,
      OBS_KEY_F20,
      OBS_KEY_F21,
      OBS_KEY_F22,
      OBS_KEY_F23,
      OBS_KEY_F24,
      OBS_KEY_SPACE,
      OBS_KEY_APOSTROPHE,
      OBS_KEY_PLUS,
      OBS_KEY_COMMA,
      OBS_KEY_MINUS,
      OBS_KEY_PERIOD,
      OBS_KEY_SLASH,
      OBS_KEY_0,
      OBS_KEY_1,
      OBS_KEY_2,
      OBS_KEY_3,
      OBS_KEY_4,
      OBS_KEY_5,
      OBS_KEY_6,
      OBS_KEY_7,
      OBS_KEY_8,
      OBS_KEY_9,
      OBS_KEY_NUMASTERISK,
      OBS_KEY_NUMPLUS,
      OBS_KEY_NUMMINUS,
      OBS_KEY_NUMPERIOD,
      OBS_KEY_NUMSLASH,
      OBS_KEY_NUM0,
      OBS_KEY_NUM1,
      OBS_KEY_NUM2,
      OBS_KEY_NUM3,
      OBS_KEY_NUM4,
      OBS_KEY_NUM5,
      OBS_KEY_NUM6,
      OBS_KEY_NUM7,
      OBS_KEY_NUM8,
      OBS_KEY_NUM9,
      OBS_KEY_SEMICOLON,
      OBS_KEY_A,
      OBS_KEY_B,
      OBS_KEY_C,
      OBS_KEY_D,
      OBS_KEY_E,
      OBS_KEY_F,
      OBS_KEY_G,
      OBS_KEY_H,
      OBS_KEY_I,
      OBS_KEY_J,
      OBS_KEY_K,
      OBS_KEY_L,
      OBS_KEY_M,
      OBS_KEY_N,
      OBS_KEY_O,
      OBS_KEY_P,
      OBS_KEY_Q,
      OBS_KEY_R,
      OBS_KEY_S,
      OBS_KEY_T,
      OBS_KEY_U,
      OBS_KEY_V,
      OBS_KEY_W,
      OBS_KEY_X,
      OBS_KEY_Y,
      OBS_KEY_Z,
      OBS_KEY_BRACKETLEFT,
      OBS_KEY_BACKSLASH,
      OBS_KEY_BRACKETRIGHT,
      OBS_KEY_ASCIITILDE,
      OBS_KEY_KANJI,
      OBS_KEY_TOUROKU,
      OBS_KEY_MASSYO,
      OBS_KEY_HANGUL,
      OBS_KEY_MOUSE1,
      OBS_KEY_MOUSE2,
      OBS_KEY_MOUSE3,
      OBS_KEY_MOUSE4,
      OBS_KEY_MOUSE5,
      OBS_KEY_LAST_VALUE
   };
   Q_ENUM(obs_key)

};

#endif // ACTIONTOSCENE_H
