#ifndef SCENETABLEUI_H
#define SCENETABLEUI_H

#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include <QTableView>
#include "streamif.h"
#include "osisif.h"

class ObsSceneSwitcher;

class SceneTableUi : public QStyledItemDelegate
{
public:
   SceneTableUi(OsisIf* osisIf, StreamIf *switcher, QTableView* actionToSceneQTV);
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
   void LoadActions(QString& inifile, OsisIf* osisIf);

   QStringList Scenes;

   QStandardItemModel* TableModel;
   StreamIf* Switcher;
   QTableView *ActionToSceneQTV;
   const QMap<int, QString>* ActionMap;
};

#endif // SCENETABLEUI_H
