#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "scenetableui.h"
#include "sceneswitcher.h"

SceneTableUi::SceneTableUi(ObsScenes *obs, ObsSceneSwitcher* switcher)
   : Switcher(switcher)
{
   TableModel = new QStandardItemModel(switcher->GetRowCount(), switcher->GetColumnCount() * 2 + 1);

   Scenes.clear();
   Scenes << "" << obs->GetScenes();

   QStringList TableHeader;
   TableHeader << "Action";
   for (int i = 0; i < switcher->GetColumnCount(); i++)
   {
      TableHeader << "Delay" << "Scene";
   }
   TableModel->setHorizontalHeaderLabels(TableHeader);

   for (int r = 0; r < switcher->GetRowCount(); r++)
   {
      QStringList row = switcher->GetRow(r);
      for (int c = 0; c < row.size(); c++)
      {
         QModelIndex index = TableModel->index(r, c, QModelIndex());
         TableModel->setData(index, QVariant(row.at(c).toLocal8Bit().constData()));
      }
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

void SceneTableUi::setEditorData(QWidget* editor, const QModelIndex& index) const
{
   int delay = 0;
   int action = index.row()+1;

   QString currentSceneOrTransition;
   switch (index.column())
   {
      case QTV_DELAY1:
      case QTV_DELAY2:
      {
         delay = index.model()->data(index, Qt::EditRole).toInt();
         QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
         spinBox->setValue(delay);
      }
      break;
      case QTV_SCENE1:
      case QTV_SCENE2:
      {
         currentSceneOrTransition = index.model()->data(index, Qt::EditRole).toString();
         QComboBox *comboBox = static_cast<QComboBox*>(editor);
         int index = comboBox->findText(currentSceneOrTransition);
         if ( index != -1 )
         {
            comboBox->setCurrentIndex(index);
         }
         else
         {
            currentSceneOrTransition.clear();
         }
      }
      break;
   }

   bool changed = false;
   Action2SceneStruct Action = ObsActions->GetActionSceneInfo(action);
   switch (index.column())
   {
      case QTV_DELAY1:
         if (Action.Delay != delay)
         {
            Action.Delay = delay;
            changed = true;
         }
         break;
      case QTV_DELAY2:
         if (Action.NextDelay != delay)
         {
            Action.NextDelay = delay;
            changed = true;
         }
         break;
      case QTV_SCENE1:
         if (QString::compare(Action.Scene, currentSceneOrTransition))
         {
            Action.Scene = currentSceneOrTransition;
            changed = true;
         }
         break;
      case QTV_SCENE2:
         if (QString::compare(Action.NextScene, currentSceneOrTransition))
         {
            Action.NextScene = currentSceneOrTransition;
            changed = true;
         }
         break;
   }
   if (changed)
   {
      ObsActions->UpdateAction(action, Action);
   }
}

void SceneTableUi::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
   int action = index.row()+1;
   QVariant value;

   switch (index.column())
   {
      case QTV_DELAY1:
      case QTV_DELAY2:
      {
         QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
         spinBox->interpretText();
         value = spinBox->value();
      }
      break;
      case QTV_SCENE1:
      case QTV_SCENE2:
      {
         QComboBox *comboBox = static_cast<QComboBox*>(editor);
         value = comboBox->currentText();
      }
      break;
   }
   model->setData(index, value, Qt::EditRole);

   if (!ObsActions)
   {
      return;
   }
   if (action)
   {
      bool changed = false;
      Action2SceneStruct ActionInfo = ObsActions->GetActionSceneInfo(action);
      switch (index.column())
      {
         case QTV_DELAY1:
            if (ActionInfo.Delay != value.toInt())
            {
               ActionInfo.Delay = value.toInt();
               changed = true;
            }
            break;
         case QTV_DELAY2:
            if (ActionInfo.NextDelay != value.toInt())
            {
               ActionInfo.NextDelay = value.toInt();
               changed = true;
            }
            break;
         case QTV_SCENE1:
            if (QString::compare(ActionInfo.Scene, value.toString()))
            {
               ActionInfo.Scene = value.toString();
               if (value.toString().isEmpty() || value.toString().isNull())
               {
                  QModelIndex newIndex = model->index(index.row(), 4, QModelIndex());
                  model->setData(newIndex, value, Qt::EditRole);
               }
               changed = true;
            }
            break;
         case QTV_SCENE2:
            if (QString::compare(ActionInfo.NextScene, value.toString()))
            {
               ActionInfo.NextScene = value.toString();
               changed = true;
            }
            break;
      }
      if (changed)
      {
         ObsActions->UpdateAction(action, ActionInfo);
      }
   }
}

void SceneTableUi::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
   editor->setGeometry(option.rect);
}

SceneTableUi::COLUMN_ENUM SceneTableUi::Column(int c)
{
   if (c == 0)
   {
      return QTV_ACTION;
   }
   return c%2 == 0 ? QTV_SCENE : QTV_DELAY;
}
