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

   int c;
   for (int r = 0; r < ActionMap->size(); r++)
   {
      c = 0;
      int actionIndex = RowActionMap.value(r);
      QModelIndex index = TableModel->index(r, c++, QModelIndex());
      TableModel->setData(index, QVariant(ActionMap->value(actionIndex)));
      for (int sceneIndex = 0; sceneIndex < NUM_SCENES_PER_ACTION; sceneIndex++)
      {
         QString scene = ActionSceneDelayMap[actionIndex][sceneIndex].first;
         int delay = ActionSceneDelayMap[actionIndex][sceneIndex].second;

         QModelIndex index1 = TableModel->index(r, c++, QModelIndex());
         TableModel->setData(index1, QVariant(delay));
         QModelIndex index2 = TableModel->index(r, c++, QModelIndex());
         TableModel->setData(index2, QVariant(scene));

         Switcher->ActionChanged(actionIndex, sceneIndex, scene, delay);
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

   QMapIterator<int, QString> actionIndexIterator(*ActionMap);
   int row = 0;
   while (actionIndexIterator.hasNext())
   {
      actionIndexIterator.next();
      QString ActionName = actionIndexIterator.value();
      IndexSceneDelayMap isdMap;
      settings.beginGroup(ActionName);
      for (int sceneIndex = 0; sceneIndex < NUM_SCENES_PER_ACTION; sceneIndex++)
      {
         SceneDelayPair sdPair;

         QString Scene = QString("SCENE%s").arg(sceneIndex + 1);
         QString Delay = QString("DELAY%s").arg(sceneIndex + 1);

         sceneName = settings.value(Scene, "").toString();
         if (!Scenes.contains(sceneName))
         {
            sceneName.clear();
         }
         sceneDelay = settings.value(Delay, "0").toInt();
         sdPair.first = sceneName;
         sdPair.second = sceneDelay;
         isdMap.insert(sceneIndex, sdPair);
      }
      ActionSceneDelayMap.insert(actionIndexIterator.key(), isdMap);
      settings.endGroup();
      RowActionMap.insert(row++, actionIndexIterator.key());
   }
}

SceneTableUi::~SceneTableUi()
{
   delete TableModel;
}

QWidget* SceneTableUi::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
   int sceneIndex = SceneIndex(index.column());
   int actionIndex = RowActionMap.value(index.row());

   switch (Column(index.column()))
   {
      case QTV_ACTION:
      {
         return new QLabel(ActionMap->value(actionIndex));
      }
      case QTV_DELAY:
      {
         QSpinBox *editor = new QSpinBox(parent);
         editor->setFrame(false);
         editor->setValue(ActionSceneDelayMap.value(actionIndex).value(sceneIndex).second);
         editor->setMinimum(0);
         editor->setMaximum(100);
         return editor;
      }
      case QTV_SCENE:
      {
         QComboBox* comboBox = new QComboBox(parent);
         comboBox->addItems(Scenes);
         int index = comboBox->findText(ActionSceneDelayMap.value(actionIndex).value(sceneIndex).first);
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
   QString scene;

   int sceneIndex = SceneIndex(index.column());
   int actionIndex = RowActionMap.value(index.row());

   switch (Column(index.column()))
   {
      case QTV_DELAY:
      {
         delay = index.model()->data(index, Qt::EditRole).toInt();
         QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
         spinBox->setValue(delay);
         if (ActionSceneDelayMap[actionIndex][sceneIndex].second != delay)
         {
            IndexSceneDelayMap iSDM = ActionSceneDelayMap[actionIndex];
            iSDM[sceneIndex].second = delay;
            Switcher->ActionChanged(actionIndex, sceneIndex, delay);
         }
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
         if (QString::compare(ActionSceneDelayMap[actionIndex][sceneIndex].first, scene))
         {
            IndexSceneDelayMap iSDM = ActionSceneDelayMap[actionIndex];
            iSDM[sceneIndex].first = scene;
            Switcher->ActionChanged(actionIndex, sceneIndex, scene);
         }
      }
      break;
   default:
      break;
   }
}

void SceneTableUi::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
   int sceneIndex = SceneIndex(index.column());
   int actionIndex = RowActionMap.value(index.row());

   switch (Column(index.column()))
   {
      case QTV_DELAY:
      {
         int delay = 0;
         QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
         spinBox->interpretText();
         delay = spinBox->value();
         if (ActionSceneDelayMap[actionIndex][sceneIndex].second != delay)
         {
            IndexSceneDelayMap iSDM = ActionSceneDelayMap[actionIndex];
            iSDM[sceneIndex].second = delay;
            model->setData(index, delay, Qt::EditRole);
            Switcher->ActionChanged(actionIndex, sceneIndex, delay);
         }
      }
      break;
      case QTV_SCENE:
      {
         QString scene;
         QComboBox *comboBox = static_cast<QComboBox*>(editor);
         scene = comboBox->currentText();
         if (QString::compare(ActionSceneDelayMap[actionIndex][sceneIndex].first, scene))
         {
            IndexSceneDelayMap iSDM = ActionSceneDelayMap[actionIndex];
            iSDM[sceneIndex].first = scene;
            Switcher->ActionChanged(actionIndex, sceneIndex, scene);
            model->setData(index, scene, Qt::EditRole);
         }
      }
      break;
   default:
      break;
   }
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

int SceneTableUi::SceneIndex(int c) const
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
