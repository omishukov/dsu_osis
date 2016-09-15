#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include <QMutexLocker>
#include "actions.h"

Actions::Actions(ActionToScene* actionInfo, QObject* parent)
   : QObject(parent)
   , OsisIf(0)
   , ActionInfo(actionInfo)
{
}

void Actions::DoActions()
{
   if (!OsisIf)
   {
      return;
   }

   QMutexLocker lock(M);

   bool passToObs;
   foreach(int action, ActionList)
   {
      SaveToFile("obs/current_action.txt", ActionInfo->GetActionName(action));

      passToObs = true;
      switch (action)
      {
         case ActionToScene::ACTION_1SC:
            break;
         case ActionToScene::ACTION_1S1:
            {
               // Save results from OsisPrfDetails
               // * points.txt
               // * tes.txt (technical element score)
               // * tcs.txt (program component score)
               SaveToFile("obs/points.txt", OsisIf->GetPoints());
               SaveToFile("obs/tes.txt", OsisIf->GetTES());
               SaveToFile("obs/tcs.txt", OsisIf->GetTCS());
               SaveToFile("obs/bonus.txt", OsisIf->GetBonus());
               SaveToFile("obs/deduction.txt", OsisIf->GetDeduction());
            }
            break;
         case ActionToScene::ACTION_1S2:
            {
               // Save rank from Performance
               SaveToFile("obs/current_participant_rank.txt", OsisIf->GetRank());

               // Segment Result list
               QMap<int, QList<QString>> SegmentResultList;
               OsisIf->GetSegmentResultList(SegmentResultList);
               GenerateSegmentResultListHtml(SegmentResultList);
            }
            break;
         case ActionToScene::ACTION_1S3:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_1S4:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_1S5:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_2SC:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_3SC:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_CLR:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_ELM:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_ELS:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_INI:
            {
               // Generate Starting order from Performances (list) and Participants.
               // starting_list.csv
               SaveToFile("obs/current_skater.txt", OsisIf->GetCurrentSkaterName());
               SaveToFile("obs/current_start_number.txt", OsisIf->GetCurrentSkaterNumber());
               SaveToFile("obs/current_skater_club.txt", OsisIf->GetCurrentSkaterClub());
               SaveToFile("obs/current_skater_nation.txt", OsisIf->GetCurrentSkaterNation());

               QMap<int, QList<QString>> SegmentStartList;
               OsisIf->GetSegmentStartList(SegmentStartList);
               GenerateHtml(SegmentStartList);
            }
            break;
         case ActionToScene::ACTION_IDT:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_IRS:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_JDG:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_LTV:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_NAM:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_NXP:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_RES:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_SEG:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_STL:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_STP:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_NXT:
            {
               SaveToFile("obs/current_skater.txt", OsisIf->GetCurrentSkaterName());
               SaveToFile("obs/current_start_number.txt", OsisIf->GetCurrentSkaterNumber());
               SaveToFile("obs/current_skater_club.txt", OsisIf->GetCurrentSkaterClub());
               SaveToFile("obs/current_skater_nation.txt", OsisIf->GetCurrentSkaterNation());
            }
            break;
         case ActionToScene::ACTION_PRV:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TBW:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TFW:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TR1:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TR2:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TST:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TPA:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TCL:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_TIM:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_URK:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_VTR:
            // Do nothing yet
            break;
         case ActionToScene::ACTION_WUP:
            // Do nothing yet
            break;
         case ActionToScene::EVENT_OVERVIEW:
            SaveToFile("obs/event_name.txt", OsisIf->GetEventName());
            break;
         case ActionToScene::SEGMENT_START:
            {
            SaveToFile("obs/segment_name.txt", OsisIf->GetSegmentName());
            SaveToFile("obs/category_name.txt", OsisIf->GetCategoryName());
            }
            break;
         case ActionToScene::PRF_RANKING:
            break;
         case ActionToScene::SEGMENT_RESULT_LIST:
            // Generate HTML Table with Segment result
            break;
         case ActionToScene::CATEGORY_RESULT_LIST:
            break;
         default:
            passToObs = false;
            break;
      }
      if (passToObs)
      {
         emit SendOsisEvent(action);
      }
   }
   ActionList.clear();
}

void Actions::AddAction(int action)
{
   if (action > ActionToScene::NO_ACTIONS && action < ActionToScene::LAST_ACTION)
   {
      ActionList.push_back(action);
   }
}

void Actions::SaveToFile(const QString& fileName, const QString text)
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
   html += "<body class=\"PageBody\"  onload=\"JavaScript:timedRefresh(3000);\">";
   html += "<table width=\"100%\" align=\"center\" border=\"0\" cellspacing=\"1\">";
   for (auto startNum : segmentStartList.keys())
   {
      QList<QString> info = segmentStartList[startNum];
      html += "<tr class=\"Line1White\">";
      html += "<td>" + QString::number(startNum) + "</td>";
      html += "<td class=\"CellLeft\"><a>" + info[0] + "</a></td>";
      html += "<td>" + info[1] + "</td></tr>";
   }
   html += "</table></body></html>";
   SaveToFile("obs/starting_order.html", html);
}

void Actions::GenerateSegmentResultListHtml(QMap<int, QList<QString> >& segmentResultList)
{
   QString html;
   html = "<html>";
   html +="<head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\"> ";
   html += "<script type=\"text/JavaScript\"> function timedRefresh(timeoutPeriod) { setTimeout(\"location.reload(true);\",timeoutPeriod);}</script>";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html += "<body class=\"PageBody\"  onload=\"JavaScript:timedRefresh(3000);\">";
   html += "<table width=\"100%\" align=\"center\" border=\"0\" cellspacing=\"1\">";
   for (auto rank : segmentResultList.keys())
   {
      QList<QString> info = segmentResultList[rank];
      html += "<tr class=\"Line1White\">";
      html += "<td>" + QString::number(rank) + "</td>";
      html += "<td class=\"CellLeft\"><a>" + info[0] + "</a></td>";
      html += "<td class=\"CellLeft\"><a>" + info[1] + "</a></td>";
      html += "<td>" + info[2] + "</td></tr>";
   }
   html += "</table></body></html>";
   SaveToFile("obs/segment_result_list.html", html);
}
