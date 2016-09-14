#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "scenetableui.h"
#include "sceneswitcher.h"

SceneTableUi::SceneTableUi(MainWindow *mainWindow)
   : ObsActions(0)
   , ObsSwitcher(0)
   , MainWindow(mainWindow)
{
}

void SceneTableUi::SetObsScenesList(const QList<QString> obsScenesList)
{
    Scenes.clear();
    Scenes << "";
    for (auto scene:obsScenesList)
    {
       Scenes << scene;
    }
}

void SceneTableUi::SetObsTransitionList(const QList<QString> obsTransitionList)
{
   Transitions.clear();
   for (auto transition:obsTransitionList)
   {
      Transitions << transition;
   }
}

QWidget* SceneTableUi::createEditor(QWidget* parent, const QStyleOptionViewItem& /*option*/, const QModelIndex& index) const
{
   int action = index.row()+1;
   if (!ObsActions)
   {
      return 0;
   }

   int delay = 0;
   QString currentSceneOrTransition;
   switch (index.column())
   {
      case QTV_DELAY1:
         delay = ObsActions[action].Delay;
         break;
      case QTV_DELAY2:
         delay = ObsActions[action].NextDelay;
         break;
      case QTV_SCENE1:
         currentSceneOrTransition = ObsActions[action].Scene;
         break;
      case QTV_SCENE2:
         currentSceneOrTransition = ObsActions[action].NextScene;
         break;
      case QTV_TRANSITION:
         currentSceneOrTransition = ObsActions[action].Transition;
         break;
   }

   switch (index.column())
   {
      case QTV_ACTION:
      {
         return new QLabel(ObsActions[action].ActionName);
      }
      case QTV_DELAY1:
      case QTV_DELAY2:
      {
         QSpinBox *editor = new QSpinBox(parent);
         editor->setFrame(false);
         editor->setValue(delay);
         editor->setMinimum(0);
         editor->setMaximum(100);

         return editor;
      }
      case QTV_SCENE1:
      case QTV_SCENE2:
      case QTV_TRANSITION:
      {
         QComboBox* comboBox = new QComboBox(parent);
         comboBox->addItems(index.column() == QTV_TRANSITION?Transitions:Scenes);
         int index = comboBox->findText(currentSceneOrTransition);
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
      case QTV_TRANSITION:
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
   switch (index.column())
   {
      case QTV_DELAY1:
         if (ObsActions[action].Delay == delay)
         {
            ObsActions[action].Delay = delay;
            changed = true;
         }
         break;
      case QTV_DELAY2:
         if (ObsActions[action].NextDelay == delay)
         {
            ObsActions[action].NextDelay = delay;
            changed = true;
         }
         break;
      case QTV_SCENE1:
         if (QString::compare(ObsActions[action].Scene, currentSceneOrTransition))
         {
            ObsActions[action].Scene = currentSceneOrTransition;
            changed = true;
         }
         break;
      case QTV_SCENE2:
         if (QString::compare(ObsActions[action].NextScene, currentSceneOrTransition))
         {
            ObsActions[action].NextScene = currentSceneOrTransition;
            changed = true;
         }
         break;
      case QTV_TRANSITION:
         if (QString::compare(ObsActions[action].Transition, currentSceneOrTransition))
         {
            ObsActions[action].Transition = currentSceneOrTransition;
            changed = true;
         }
         break;
   }
   if (changed)
   {
      MainWindow->UpdateSceneConfiguration();
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
      case QTV_TRANSITION:
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
      switch (index.column())
      {
         case QTV_DELAY1:
            if (ObsActions[action].Delay != value.toInt())
            {
               ObsActions[action].Delay = value.toInt();
               changed = true;
            }
            break;
         case QTV_DELAY2:
            if (ObsActions[action].NextDelay != value.toInt())
            {
               ObsActions[action].NextDelay = value.toInt();
               changed = true;
            }
            break;
         case QTV_SCENE1:
            if (QString::compare(ObsActions[action].Scene, value.toString()))
            {
               ObsActions[action].Scene = value.toString();
               if (value.toString().isEmpty() || value.toString().isNull())
               {
                  QModelIndex newIndex = model->index(index.row(), 4, QModelIndex());
                  model->setData(newIndex, value, Qt::EditRole);
               }
               changed = true;
            }
            break;
         case QTV_SCENE2:
            if (QString::compare(ObsActions[action].NextScene, value.toString()))
            {
               ObsActions[action].NextScene = value.toString();
               changed = true;
            }
            break;
         case QTV_TRANSITION:
            if (QString::compare(ObsActions[action].Transition, value.toString()))
            {
               ObsActions[action].Transition = value.toString();
               changed = true;
            }
            break;
      }
      if (changed)
      {
         MainWindow->UpdateSceneConfiguration();
      }
   }
}

void SceneTableUi::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& /*index*/) const
{
   editor->setGeometry(option.rect);
}
