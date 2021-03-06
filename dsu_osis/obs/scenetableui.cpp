#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include "scenetableui.h"
#include "sceneswitcher.h"

SceneTableUi::SceneTableUi()
   : ObsActions(0)
   , ObsScenesList(0)
   , ObsTransitionList(0)
   , ObsSwitcher(0)
{
}

void SceneTableUi::SetObsScenesList(const QList<SceneInfo*>* obsScenesList)
{
    ObsScenesList = obsScenesList;
    if (ObsScenesList)
    {
       Scenes.clear();
       Scenes << "";
       for (auto scene:(*ObsScenesList))
       {
          Scenes << scene->SceneName;
       }
    }
}

void SceneTableUi::SetObsTransitionList(const QList<SceneInfo*>* obsTransitionList)
{
   ObsTransitionList = obsTransitionList;
   if (ObsTransitionList)
   {
      Transitions.clear();
      for (auto transition:(*ObsTransitionList))
      {
         Transitions << transition->SceneName;
      }
   }
}

QWidget* SceneTableUi::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   ObsAction* action = 0;
   if (ObsActions)
   {
      action = (*ObsActions)[index.row()+1];
   }

   int delay = 0;
   QString currentSceneOrTransition;
   switch (index.column())
   {
      case QTV_DELAY1:
         delay = action ? action->GetDelay1():0;
         break;
      case QTV_DELAY2:
         delay = action ? action->GetDelay2():0;
         break;
      case QTV_SCENE1:
         currentSceneOrTransition = action ? action->GetScene1Name():"";
         break;
      case QTV_SCENE2:
         currentSceneOrTransition = action ? action->GetScene2Name():"";
         break;
      case QTV_TRANSITION:
         currentSceneOrTransition = action ? action->GetTransitionName():"";
         break;
   }

   switch (index.column())
   {
      case QTV_ACTION:
      {
         return new QLabel(action ? action->actionName:"");
      }
      break;
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
      break;
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
      break;
   }
}

void SceneTableUi::setEditorData(QWidget* editor, const QModelIndex& index) const
{
   int delay = 0;
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
      }
      break;
   }
}

void SceneTableUi::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
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

   ObsAction* action = 0;
   if (ObsActions)
   {
      action = (*ObsActions)[index.row()+1];
   }
   if (action)
   {
      bool changed = false;
      switch (index.column())
      {
         case QTV_DELAY1:
            if (action->GetDelay1() != value.toInt())
            {
               action->SetDelay1(value.toInt());
               changed = true;
            }
            break;
         case QTV_DELAY2:
            if (action->GetDelay2() != value.toInt())
            {
               action->SetDelay2(value.toInt());
               changed = true;
            }
            break;
         case QTV_SCENE1:
            if (QString::compare(action->GetScene1Name(), value.toString()))
            {
               action->SetScene1(ObsSwitcher->GetScene(value.toString()));
               changed = true;
               if (value.toString().isEmpty() || value.toString().isNull())
               {
                  QModelIndex index = model->index(index.row(), 4, QModelIndex());
                  model->setData(index, value, Qt::EditRole);
               }
            }
            break;
         case QTV_SCENE2:
            if (QString::compare(action->GetScene2Name(), value.toString()))
            {
               action->SetScene2(ObsSwitcher->GetScene(value.toString()));
               changed = true;
            }
            break;
         case QTV_TRANSITION:
            if (QString::compare(action->GetTransitionName(), value.toString()))
            {
               action->SetTransition(ObsSwitcher->GetTransition(value.toString()));
               changed = true;
            }
            break;
      }
      if (changed)
      {
         ObsSwitcher->SaveActions();
      }
   }
}

void SceneTableUi::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   editor->setGeometry(option.rect);
}
