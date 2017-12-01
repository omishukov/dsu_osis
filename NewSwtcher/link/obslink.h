#ifndef OBSLINK_H
#define OBSLINK_H

#include <QWebSocket>
#include <QMutex>
#include <QMetaEnum>
#include <link/linkif.h>
#include <configuration.h>
#include "link/linkbase.h"

class ObsLink : public BaseLink
{
   Q_OBJECT
public:
   explicit ObsLink(const QString& connectionGroupName, Configuration& configFile, QObject *parent = nullptr);

signals:

public slots:
   void SlotSocketReadyRead(QString message);
   void SlotSocketError(QAbstractSocket::SocketError error);

private:
   virtual void SocketConnectRequest();
   virtual void SocketDisconnectRequest();
   virtual void SocketConnected();
   virtual void SocketDisconnected();

   void Reconnect();
   void WsRequest(int key);

   QWebSocket* obsWebSocketClient;
   QString Host;
   QString Port;
   QMutex M;
   bool socketReconnectNeeded;

   QMetaEnum metaWSRequest;
   QMetaEnum metaWSEvent;

public:
   enum WSRequest
   {  // obs-websocket/src/WSRequestHandler.cpp
      GetVersion,
      GetAuthRequired,
      Authenticate,
      SetHeartbeat,
      SetCurrentScene,
      GetCurrentScene,
      GetSceneList,
      SetSourceRender,
      SetSceneItemRender,
      SetSceneItemPosition,
      SetSceneItemTransform,
      SetSceneItemCrop,
      GetSceneItemProperties,
      SetSceneItemProperties,
      ResetSceneItem,
      GetStreamingStatus,
      StartStopStreaming,
      StartStopRecording,
      StartStreaming,
      StopStreaming,
      StartRecording,
      StopRecording,
      StartStopReplayBuffer,
      StartReplayBuffer,
      StopReplayBuffer,
      SaveReplayBuffer,
      SetRecordingFolder,
      GetRecordingFolder,
      GetTransitionList,
      GetCurrentTransition,
      SetCurrentTransition,
      SetTransitionDuration,
      GetTransitionDuration,
      SetVolume,
      GetVolume,
      ToggleMute,
      SetMute,
      GetMute,
      SetSyncOffset,
      GetSyncOffset,
      GetSpecialSources,
      GetSourcesList,
      GetSourceTypesList,
      GetSourceSettings,
      SetSourceSettings,
      SetCurrentSceneCollection,
      GetCurrentSceneCollection,
      ListSceneCollections,
      SetCurrentProfile,
      GetCurrentProfile,
      ListProfiles,
      SetStreamSettings,
      GetStreamSettings,
      SaveStreamSettings,
      GetStudioModeStatus,
      GetPreviewScene,
      SetPreviewScene,
      TransitionToProgram,
      EnableStudioMode,
      DisableStudioMode,
      ToggleStudioMode,
      SetTextGDIPlusProperties,
      GetTextGDIPlusProperties,
      GetBrowserSourceProperties,
      SetBrowserSourceProperties
   };
   Q_ENUM(WSRequest)
   enum WSEvent
   {
      SwitchScenes,
      ScenesChanged,
      SceneCollectionChanged,
      SceneCollectionListChanged,
      SwitchTransition,
      TransitionListChanged,
      TransitionDurationChanged,
      TransitionBegin,
      ProfileChanged,
      ProfileListChanged,
      StreamStarting,
      StreamStarted,
      StreamStopping,
      StreamStopped,
      StreamStatus,
      RecordingStarting,
      RecordingStarted,
      RecordingStopping,
      RecordingStopped,
      ReplayStarting,
      ReplayStarted,
      ReplayStopping,
      ReplayStopped,
      Exiting,
      Heartbeat,
      SourceOrderChanged,
      SceneItemAdded,
      SceneItemRemoved,
      SceneItemVisibilityChanged,
      PreviewSceneChanged,
      StudioModeSwitched
   };
   Q_ENUM(WSEvent)
};

#endif // OBSLINK_H
