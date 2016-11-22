#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QSettings>
#include "scenetableui.h"

const int NUM_SCENES_PER_ACTION = 2;

SceneTableUi::SceneTableUi(QString& inifile, OsisIf* osisIf, StreamIf* switcher, QTableView* actionToSceneQTV)
   : Switcher(switcher)
   , ActionToSceneQTV(actionToSceneQTV)
   , ActionMap(osisIf->GetActions())
{
   LoadActions(inifile);

   TableModel = new QStandardItemModel(ActionMap->size(), NUM_SCENES_PER_ACTION * 2 + 1);

   Scenes << "" << switcher->GetScenes();

   QStringList TableHeader;
   TableHeader << "Action";
   for (int i = 0; i < NUM_SCENES_PER_ACTION; i++)
   {
      TableHeader << "Delay" << "Scene";
   }
   TableModel->setHorizontalHeaderLabels(TableHeader);

   int c = 0;
   for (int r = 0; r < ActionMap->size(); r++)
   {
      int action = RowActionMap.value(r);
      QModelIndex index = TableModel->index(r, c++, QModelIndex());
      TableModel->setData(index, QVariant(ActionMap->value(action)));
      for (int i = 0; i < NUM_SCENES_PER_ACTION; i++)
      {
         QModelIndex index1 = TableModel->index(r, c++, QModelIndex());
         TableModel->setData(index1, QVariant(ActionSceneDelayMap.value(action).value(i).key()));
         QModelIndex index2 = TableModel->index(r, c++, QModelIndex());
         TableModel->setData(index2, QVariant(sd.key()));
      }
      QMapIterator<QString, int> sd(ActionSceneDelayMap.value(action));
      int i = 0;
      while (sd.hasNext() && i < NUM_SCENES_PER_ACTION)
      {
         sd.next();
         QModelIndex index1 = TableModel->index(r, c++, QModelIndex());
         TableModel->setData(index1, QVariant(sd.value()));
         QModelIndex index2 = TableModel->index(r, c++, QModelIndex());
         TableModel->setData(index2, QVariant(sd.key()));
         i++;
      }
   }
   ActionToSceneQTV->setModel(TableModel);
   ActionToSceneQTV->setItemDelegate(this);
   ActionToSceneQTV->resizeColumnsToContents();
   ActionToSceneQTV->show();
//   ActionToSceneQTV->hideRow();
}

void SceneTableUi::LoadActions(QString& inifile)
{
   Inifile = inifile;
   QSettings settings(Inifile, QSettings::IniFormat);
   QString sceneName;
   int sceneDelay;

   QMapIterator<int, QString> i(*ActionMap);
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
         if (!Scenes.contains(sceneName))
         {
            sceneName.clear();
         }
         sceneDelay = settings.value(Delay, "0").toInt();
         SceneDelayMap.insert(sceneName, sceneDelay);
      }
      settings.endGroup();
      ActionSceneDelayMap.insert(i.key(), SceneDelayMap);
      RowActionMap.insert(row++, i.key());
   }
}

SceneTableUi::~SceneTableUi()
{
   delete TableModel;
}

QWidget* SceneTableUi::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
   int column = Column(index.column());
   int action = RowActionMap.value(index.row());
   QMapIterator<QString, int> sd(ActionSceneDelayMap.value(action));
   int i = 0;
   while (sd.hasNext() && i < column)
   {
      sd.next();
   }
   switch (Column(index.column()))
   {
      case QTV_ACTION:
      {
         return new QLabel(ActionMap->value(action));
      }
      case QTV_DELAY:
      {
         QSpinBox *editor = new QSpinBox(parent);
         editor->setFrame(false);
         editor->setValue(sd.value());
         editor->setMinimum(0);
         editor->setMaximum(100);
         return editor;
      }
      case QTV_SCENE:
      {
         QComboBox* comboBox = new QComboBox(parent);
         comboBox->addItems(Scenes);
         int index = comboBox->findText(sd.key());
         if ( index != -1 )
         {
            comboBox->setCurrentIndex(index);
         }
         return comboBox;
      }
   }
   return 0;
}

void SceneTableUi::setEditorData(QWidget* editor, const QModelIndex& index) const
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
