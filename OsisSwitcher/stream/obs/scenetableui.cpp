#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "scenetableui.h"

const int NUM_SCENES_PER_ACTION = 2;

SceneTableUi::SceneTableUi(OsisIf* osisIf, StreamIf* switcher, QTableView* actionToSceneQTV)
   : Switcher(switcher)
   , ActionToSceneQTV(actionToSceneQTV)
   , ActionMap(osisIf->GetActions())
{
   TableModel = new QStandardItemModel(ActionMap->size(), NUM_SCENES_PER_ACTION * 2 + 1);

   Scenes << "" << switcher->GetScenes();

   QStringList TableHeader;
   TableHeader << "Action";
   for (int i = 0; i < NUM_SCENES_PER_ACTION; i++)
   {
      TableHeader << "Delay" << "Scene";
   }
   TableModel->setHorizontalHeaderLabels(TableHeader);

   for (int r = 0; r < ActionMap->size(); r++)
   {
      QStringList row = switcher->GetRow(r);
      for (int c = 0; c < row.size(); c++)
      {
         QModelIndex index = TableModel->index(r, c, QModelIndex());
         TableModel->setData(index, QVariant(row.at(c).toLocal8Bit().constData()));
      }
   }
   ActionToSceneQTV->setModel(TableModel);
   ActionToSceneQTV->setItemDelegate(this);
   ActionToSceneQTV->resizeColumnsToContents();
   ActionToSceneQTV->show();

}

void SceneTableUi::LoadActions(QString& inifile, OsisIf* osisIf)
{
   Inifile = inifile;
   QSettings settings(Inifile, QSettings::IniFormat);
   QString sceneName;
   int sceneDelay;

   const QMap<int, QString>* actionList = osisIf->GetActions();
   QMapIterator<int, QString> i(*actionList);
   int row = 0;
   while (i.hasNext())
   {
      i.next();
      QString ActionName = i.value();
      QMap<QString, int> SceneDelayMap;

      settings.beginGroup(ActionName);
      for (int sc = 0; sc < NUM_SCENES_PER_ACTION; sc++)
      {
         QString Scene = QString("SCENE%s").arg(sc + 1);
         QString Delay = QString("DELAY%s").arg(sc + 1);
         sceneName = settings.value(Scene, "").toString();
         sceneDelay = settings.value(Delay, "0").toInt();
         SceneDelayMap.insert(sceneName, sceneDelay);
      }
      settings.endGroup();

      ObsActions.insert(i.key(), new ObsAction(ActionName, SceneDelayMap, osisIf));
Move it to ConfigUI:      RowActionMap.insert(row++, i.key());
   }
}

SceneTableUi::~SceneTableUi()
{
   delete TableModel;
}

QWidget* SceneTableUi::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
   int row = index.row();

   QStringList rowList = Switcher->GetRow(row);
   switch (Column(index.column()))
   {
      case QTV_ACTION:
         return new QLabel(rowList.at(index.column()).toLocal8Bit().constData());
      case QTV_DELAY:
      {
         QSpinBox *editor = new QSpinBox(parent);
         editor->setFrame(false);
         editor->setValue(rowList.at(index.column()).toInt());
         editor->setMinimum(0);
         editor->setMaximum(100);
         return editor;
      }
      case QTV_SCENE:
      {
         QComboBox* comboBox = new QComboBox(parent);
         comboBox->addItems(Scenes);
         int index = comboBox->findText(rowList.at(index.column()).toLocal8Bit().constData());
         if ( index != -1 )
         {
            comboBox->setCurrentIndex(index);
         }
         return comboBox;
      }
   }
   return 0;
}

void SceneTableUi::setEditorData(QWid1get* editor, const QModelIndex& index) const
{
   int delay = 0;
   int action = index.row()+1;

   QString scene;
   switch (Column(index.column()))
   {
      case QTV_DELAY:
      {
         delay = index.model()->data(index, Qt::EditRole).toInt();
         QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
         spinBox->setValue(delay);
         Switcher->SetDelay(action, SceneIndex(index.column()), delay);
      }
      break;
      case QTV_SCENE:
      {
         scene = index.model()->data(index, Qt::EditRole).toString();
         QComboBox *comboBox = static_cast<QComboBox*>(editor);
         int index = comboBox->findText(scene);
         if ( index != -1 )
         {
            comboBox->setCurrentIndex(index);
         }
         else
         {
            scene.clear();
         }
         Switcher->SetScene(action, SceneIndex(index.column()), scene);
      }
      break;
   }
}

void SceneTableUi::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
   int action = index.row()+1;
   QVariant value;

   switch (Column(index.column()))
   {
      case QTV_DELAY:
      {
         QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
         spinBox->interpretText();
         value = spinBox->value();
         Switcher->SetDelay(action, SceneIndex(index.column()), value.toInt());
      }
      break;
      case QTV_SCENE:
      {
         QComboBox *comboBox = static_cast<QComboBox*>(editor);
         value = comboBox->currentText();
         Switcher->SetScene(action, SceneIndex(index.column()), value.toString());
      }
      break;
   }
   model->setData(index, value, Qt::EditRole);
}

void SceneTableUi::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
   editor->setGeometry(option.rect);
}

SceneTableUi::COLUMN_ENUM SceneTableUi::Column(int c) const
{
   if (c == 0)
   {
      return QTV_ACTION;
   }
   return c%2 == 0 ? QTV_SCENE : QTV_DELAY;
}

int SceneTableUi::SceneIndex(int c)
{
   if (c == 0)
   {
      return -1;
   }
   if (c%2)
   {
      c++;
   }
   return c/2 - 1;
}
