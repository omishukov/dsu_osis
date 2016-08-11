#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include "actions.h"

Actions::Actions()
   : MetaActionsEnum(QMetaEnum::fromType<ObsAction>())
   , OsisIf(0)
{
}

void Actions::DoActions()
{
   if (!OsisIf)
   {
      return;
   }

   foreach(int action, ActionList)
   {
      QString actionName = MetaActionsEnum.valueToKey(action);
      SaveToFile("obs/current_action.txt", actionName);

      switch (action)
      {
         case ACTION_1SC:
            break;
         case ACTION_1S1:
            // Save results from OsisPrfDetails
            // * points.txt
            // * tes.txt
            // * tcs.txt
            break;
         case ACTION_1S2:
            // Save rank from Performance (ID from Current Action, Current_Participant_ID)
            break;
         case ACTION_1S3:
            // Do nothing yet
            break;
         case ACTION_1S4:
            // Do nothing yet
            break;
         case ACTION_1S5:
            // Do nothing yet
            break;
         case ACTION_2SC:
            // Do nothing yet
            break;
         case ACTION_3SC:
            // Do nothing yet
            break;
         case ACTION_CLR:
            // Do nothing yet
            break;
         case ACTION_ELM:
            // Do nothing yet
            break;
         case ACTION_ELS:
            // Do nothing yet
            break;
         case ACTION_INI:
            {
               // Generate Starting order from Performances (list) and Participants.
               // starting_list.csv

               QString CurrentSkater = OsisIf->GetCurrentSkaterName();
               SaveToFile("obs/current_skater.txt", CurrentSkater);

               QMap<int, QList<QString>> SegmentStartList;
               OsisIf->GetSegmentStartList(SegmentStartList);
               GenerateHtml(SegmentStartList);

            }
            break;
         case ACTION_IDT:
            // Do nothing yet
            break;
         case ACTION_IRS:
            // Do nothing yet
            break;
         case ACTION_JDG:
            // Do nothing yet
            break;
         case ACTION_LTV:
            // Do nothing yet
            break;
         case ACTION_NAM:
            // Do nothing yet
            break;
         case ACTION_NXP:
            // Do nothing yet
            break;
         case ACTION_RES:
            // Do nothing yet
            break;
         case ACTION_SEG:
            // Do nothing yet
            break;
         case ACTION_STL:
            // Do nothing yet
            break;
         case ACTION_STP:
            // Do nothing yet
            break;
         case ACTION_NXT:
            {
               // Save current skater
               // * current_skater.txt
               QString CurrentSkater = OsisIf->GetCurrentSkaterName();
               SaveToFile("obs/current_skater.txt", CurrentSkater);
            }
            break;
         case ACTION_PRV:
            // Do nothing yet
            break;
         case ACTION_TBW:
            // Do nothing yet
            break;
         case ACTION_TFW:
            // Do nothing yet
            break;
         case ACTION_TR1:
            // Do nothing yet
            break;
         case ACTION_TR2:
            // Do nothing yet
            break;
         case ACTION_TST:
            // Do nothing yet
            break;
         case ACTION_TPA:
            // Do nothing yet
            break;
         case ACTION_TCL:
            // Do nothing yet
            break;
         case ACTION_TIM:
            // Do nothing yet
            break;
         case ACTION_URK:
            // Do nothing yet
            break;
         case ACTION_VTR:
            // Do nothing yet
            break;
         case ACTION_WUP:
            // Do nothing yet
            break;
         case EVENT_OVERVIEW:
            break;
         case SEGMENT_START:
            break;
         case PRF_RANKING:
            break;
         case SEGMENT_RESULT_LIST:
            // Generate HTML Table with Segment result
            break;
         case CATEGORY_RESULT_LIST:
            break;
         default:
            break;
      }
   }
   ActionList.clear();
}

void Actions::AddAction(int action)
{
   ActionList.push_back(action);
}

void Actions::SaveToFile(const QString& fileName, const QString& text)
{
   QFileInfo info(fileName);
   if (!info.exists())
   {
      if (!QDir(info.path()).exists())
      {
         QDir().mkdir(info.path());
      }
   }
   QFile file(fileName);
   if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
   {
      QTextStream stream(&file);
      stream << text << endl;
   }
}

void Actions::GenerateHtml(QMap<int, QList<QString> >& segmentStartList)
{
   QString html;
   html = "<html>";
   html +="<head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> ";
   html += "<script type=\"text/JavaScript\"> function timedRefresh(timeoutPeriod) { setTimeout(\"location.reload(true);\",timeoutPeriod);}</script>";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html
}
