#ifndef SCENETABLEUI_H
#define SCENETABLEUI_H

#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include "obsaction.h"
#include "sceneinfo.h"
#include "obsscenes.h"
#include "streamif.h"

class ObsSceneSwitcher;

class SceneTableUi : public QStyledItemDelegate
{
public:
   SceneTableUi(QStringList &scenes, StreamIf *switcher);
   ~SceneTableUi();

   enum COLUMN_ENUM
   {
      QTV_ACTION,
      QTV_DELAY,
      QTV_SCENE,
   };

public: // QStyledItemDelegate
   QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
   void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const Q_DECL_OVERRIDE;

public:
   QStandardItemModel* GetModel() { return TableModel; }
signals:
   void UpdateActions();

public slots:

private:
   COLUMN_ENUM Column(int c) const;
   int SceneIndex(int c);

   QStringList Scenes;

   QStandardItemModel* TableModel;
   StreamIf* Switcher;
};

#endif // SCENETABLEUI_H
