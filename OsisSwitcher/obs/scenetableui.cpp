#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "scenetableui.h"
#include "sceneswitcher.h"

SceneTableUi::SceneTableUi()
   : ObsActions(0)
{
}

void SceneTableUi::SetObsActions(ActionToScene* obsActions)
{
    ObsActions = obsActions;

    QList<QString> obsScenesList = ObsActions->GetSceneList();
    Scenes.clear();
    Scenes << "";
    for (auto scene:obsScenesList)
    {
       Scenes << scene;
    }

   QList<QString> obsTransitionList = ObsActions->GetTransitionList();
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
   Action2SceneStruct Action = ObsActions->GetActionSceneInfo(action);
   switch (index.column())
   {
      case QTV_DELAY1:
         delay = Action.Delay;
         break;
      case QTV_DELAY2:
         delay = Action.NextDelay;
         break;
      case QTV_SCENE1:
         currentSceneOrTransition = Action.Scene;
         break;
      case QTV_SCENE2:
         currentSceneOrTransition = Action.NextScene;
         break;
      case QTV_TRANSITION:
         currentSceneOrTransition = Action.Transition;
         break;
   }

   switch (index.column())
   {
      case QTV_ACTION:
      {
         return new QLabel(Action.ActionName);
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
      case QTV_TRANSITION:
         if (QString::compare(Action.Transition, currentSceneOrTransition))
         {
            Action.Transition = currentSceneOrTransition;
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
         case QTV_TRANSITION:
            if (QString::compare(ActionInfo.Transition, value.toString()))
            {
               ActionInfo.Transition = value.toString();
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
