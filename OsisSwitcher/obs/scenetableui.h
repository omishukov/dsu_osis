#ifndef SCENETABLEUI_H
#define SCENETABLEUI_H

#include <QStyledItemDelegate>
#include "obsaction.h"
#include "sceneinfo.h"

class ObsSceneSwitcher;

class SceneTableUi : public QStyledItemDelegate
{
public:
   SceneTableUi();

   enum
   {
      QTV_ACTION,
      QTV_DELAY1,
      QTV_SCENE1,
      QTV_DELAY2,
      QTV_SCENE2,
      QTV_TRANSITION
   };

   void SetObsActions(QMap<int, ObsAction*> *obsActions) { ObsActions = obsActions; }
   void SetObsScenesList(const QList<SceneInfo*> *obsScenesList);
   void SetObsTransitionList(const QList<SceneInfo*> *obsTransitionList);
   void SetObsSwither(ObsSceneSwitcher* oSS) {ObsSwitcher = oSS;}

public:
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const Q_DECL_OVERRIDE;

   void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
   void setModelData(QWidget *editor, QAbstractItemModel *model,
                     const QModelIndex &index) const Q_DECL_OVERRIDE;

   void updateEditorGeometry(QWidget *editor,
       const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
   QMap<int, ObsAction*> *ObsActions;
   const QList<SceneInfo*> *ObsScenesList;
   const QList<SceneInfo*> *ObsTransitionList;
   QStringList Scenes;
   QStringList Transitions;
   ObsSceneSwitcher* ObsSwitcher;

};

#endif // SCENETABLEUI_H
