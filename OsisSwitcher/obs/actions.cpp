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
               SaveToFile("obs/points.txt", OsisIf->GetPoints());
               SaveToFile("obs/tes.txt", OsisIf->GetTES());
               SaveToFile("obs/tcs.txt", OsisIf->GetTCS());
               SaveToFile("obs/bonus.txt", OsisIf->GetBonus());
               SaveToFile("obs/deduction.txt", OsisIf->GetDeduction());
            }
            break;
         case ActionToScene::ACTION_1S2:
            {
               SaveToFile("obs/current_participant_rank.txt", OsisIf->GetRank());

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
               SaveToFile("obs/current_skater.txt", OsisIf->GetCurrentSkaterName());
               SaveToFile("obs/current_start_number.txt", OsisIf->GetCurrentSkaterNumber());
               SaveToFile("obs/current_skater_club.txt", OsisIf->GetCurrentSkaterClub());
               SaveToFile("obs/current_skater_nation.txt", OsisIf->GetCurrentSkaterNation());

               QMap<int, QList<QString>> SegmentStartList;
               OsisIf->GetSegmentStartList(SegmentStartList);
               GenerateHtml(SegmentStartList);

               OsisIf->GetWarmUpGroupsList(WarmUpList);
               QMap<int, QList<QString>> WarmUpGroupNameList;
               OsisIf->GetWarmUpStartList(WarmUpGroupNameList);
               GenerateWarmUpStartListHtml(WarmUpGroupNameList);
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
            {
               SaveToFile("obs/current_skater.txt", "");
               SaveToFile("obs/current_start_number.txt", "");
               SaveToFile("obs/current_skater_club.txt", "");
               SaveToFile("obs/current_skater_nation.txt", "");
               SaveToFile("obs/points.txt", "");
               SaveToFile("obs/tes.txt", "");
               SaveToFile("obs/tcs.txt", "");
               SaveToFile("obs/bonus.txt", "");
               SaveToFile("obs/deduction.txt", "");
               SaveToFile("obs/current_warmup_group_number.txt", "");
            }
            break;
         case ActionToScene::ACTION_NXT:
            {
               int stnum = OsisIf->GetCurrentSkaterNumber().toInt();
               if (stnum)
               {
                  QMap<int, QList<QString>> WarmUpGroupNameList;
                  OsisIf->GetWarmUpStartList(WarmUpGroupNameList);
                  GenerateWarmUpStartListHtml(WarmUpGroupNameList);
                  SaveToFile("obs/current_warmup_group_number.txt", OsisIf->GetCurrentWarmUpGroupNumber());
                  for (auto group:WarmUpList)
                  {
                     if (stnum == group+1)
                     {
                        action = ActionToScene::ACTION_WUP;
                     }
                  }
               }
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
         {
            SaveToFile("obs/event_name.txt", OsisIf->GetEventName());
            SaveToFile("obs/event_abbreviation.txt", OsisIf->GetEventAbbreviation());
          }
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
            {
               QMap<int, QList<QString>> SegmentResultList;
               OsisIf->GetSegmentResultList(SegmentResultList);
               if (SegmentResultList.isEmpty())
               {
                  passToObs = false;
               }
               GenerateSegmentResultListHtml(SegmentResultList);
            }
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

void Actions::SaveToFile(const QString& fileName, QString text)
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
      stream.setCodec("UTF-8");
      stream << text << endl;
   }
}

void Actions::GenerateHtml(QMap<int, QList<QString> >& segmentStartList)
{
   QString html;
   html = "<html>";
   html +="<head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\"> ";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html += "<body class=\"PageBody\">";
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
   html +="<head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\"> ";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html += "<body class=\"PageBody\">";
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

void Actions::GenerateWarmUpStartListHtml(QMap<int, QList<QString> >& warmUpGroupNameList)
{
   QString html;
   html = "<html>";
   html += "<head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\"> ";
   html += "<META HTTP-EQUIV=\"refresh\" CONTENT=\"5\"; URL=http://localhost:8080/current_warmup_group.html\">";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html += "<body class=\"PageBody\">";
   html += "<table width=\"100%\" align=\"center\" border=\"0\" cellspacing=\"1\">";
   for (auto key : warmUpGroupNameList.keys())
   {
      QList<QString> info = warmUpGroupNameList[key];
      html += "<tr class=\"Line1White\">";
      html += "<td>" + QString::number(key) + "</td>";
      html += "<td class=\"CellLeft\"><a>" + info[0] + "</a></td>";
      html += "<td>" + info[1] + "</td></tr>";
   }
   html += "</table></body></html>";
   SaveToFile("obs/current_warmup_group.html", html);
}
