#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include <QMutexLocker>
#include "actions.h"

const int MAX_LIST_ENTRIES = 8;

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
      GenerateHtml("obs/current_action", ActionInfo->GetActionName(action));

      passToObs = true;
      switch (action)
      {
         case ActionToScene::ACTION_1SC:
            break;
         case ActionToScene::ACTION_1S1:
            {
               GenerateHtml("obs/points", OsisIf->GetPoints());
               GenerateHtml("obs/tes", OsisIf->GetTES());
               GenerateHtml("obs/tcs", OsisIf->GetTCS());
               GenerateHtml("obs/bonus", OsisIf->GetBonus());
               GenerateHtml("obs/deduction", OsisIf->GetDeduction());
            }
            break;
         case ActionToScene::ACTION_1S2:
            {
               GenerateHtml("obs/current_participant_rank", OsisIf->GetRank());

               QMap<int, QList<QString>> SegmentResultList;
               OsisIf->GetSegmentResultList(SegmentResultList);
               GenerateHtml("obs/segment_result_list.html", SegmentResultList);
            }
            break;
         case ActionToScene::ACTION_1S3:
            {
               GenerateHtml("obs/tpoints", OsisIf->GetTPoints());
               GenerateHtml("obs/current_participant_trank", OsisIf->GetTRank());

               GenerateResultHtml("obs/result/index.html");

               QMap<int, QList<QString>> CategoryResultList;
               OsisIf->GetCategoryResultList(CategoryResultList);
               GenerateHtml("obs/category_result_list.html", CategoryResultList);

               QMap<int, QList<QString>> ResultList;
               OsisIf->GetResultList(ResultList);
               GenerateNewHtmlList("obs/resultlist/index.html", ResultList, "STANDINGS");
            }
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
               GenerateHtml("obs/current_skater", OsisIf->GetCurrentSkaterName());
               GenerateHtml("obs/current_start_number", OsisIf->GetCurrentSkaterNumber());
               GenerateHtml("obs/current_skater_club", OsisIf->GetCurrentSkaterClub());
               GenerateHtml("obs/current_skater_nation", OsisIf->GetCurrentSkaterNation());

               QMap<int, QList<QString>> SegmentStartList;
               OsisIf->GetSegmentStartList(SegmentStartList);
               GenerateHtml("obs/starting_order.html", SegmentStartList);

               OsisIf->GetWarmUpGroupsList(WarmUpList);
               QMap<int, QList<QString>> WarmUpGroupNameList;
               OsisIf->GetWarmUpStartList(WarmUpGroupNameList);
               GenerateHtml("obs/current_warmup_group.html", WarmUpGroupNameList);
               GenerateHtml("obs/current_warmup_group_number", OsisIf->GetCurrentWarmUpGroupNumber());

               GenerateEventInfoHtml("obs/event/index.html");

               GenerateSkaterInfoHtml("obs/skater/index.html");

               QMap<int, QList<QString>> StartList;
               OsisIf->GetStartList(StartList);
               GenerateNewHtmlList("obs/startlist/index.html", StartList, "START LIST");

               QMap<int, QList<QString>> WarmUpEntries;
               OsisIf->GetWarmUpList(WarmUpEntries);
               GenerateNewHtmlList("obs/warmup/index.html", WarmUpEntries, "WARM UP GROUP " + OsisIf->GetCurrentWarmUpGroupNumber());
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
               GenerateHtml("obs/current_skater", "");
               GenerateHtml("obs/current_start_number", "");
               GenerateHtml("obs/current_skater_club", "");
               GenerateHtml("obs/current_skater_nation", "");
               GenerateHtml("obs/points", "");
               GenerateHtml("obs/tes", "");
               GenerateHtml("obs/tcs", "");
               GenerateHtml("obs/bonus", "");
               GenerateHtml("obs/deduction", "");
               GenerateHtml("obs/current_warmup_group_number", "");
               QMap<int, QList<QString>> SegmentStartList;
               GenerateHtml("obs/starting_order.html", SegmentStartList);
               QMap<int, QList<QString>> WarmUpGroupNameList;
               GenerateHtml("obs/current_warmup_group.html", WarmUpGroupNameList);

               QMap<int, QList<QString>> StartList;
               GenerateNewHtmlList("obs/startlist/index.html", StartList, "START LIST");

               QMap<int, QList<QString>> ResultList;
               OsisIf->GetResultList(ResultList);
               GenerateNewHtmlList("obs/resultlist/index.html", ResultList, "RESULT");
            }
            break;
         case ActionToScene::ACTION_NXT:
            {
               int stnum = OsisIf->GetCurrentSkaterNumber().toInt();
               if (stnum)
               {
                  QMap<int, QList<QString>> WarmUpGroupNameList;
                  OsisIf->GetWarmUpStartList(WarmUpGroupNameList);
                  GenerateHtml("obs/current_warmup_group.html", WarmUpGroupNameList);
                  GenerateHtml("obs/current_warmup_group_number", OsisIf->GetCurrentWarmUpGroupNumber());
                  for (auto group:WarmUpList)
                  {
                     if (stnum == group+1)
                     {
                        QMap<int, QList<QString>> WarmUpEntries;
                        OsisIf->GetWarmUpList(WarmUpEntries);
                        GenerateNewHtmlList("obs/warmup/index.html", WarmUpEntries, "WARM UP GROUP " + OsisIf->GetCurrentWarmUpGroupNumber());

                        action = ActionToScene::ACTION_WUP;
                     }
                  }
               }
               GenerateHtml("obs/current_skater", OsisIf->GetCurrentSkaterName());
               GenerateHtml("obs/current_start_number", OsisIf->GetCurrentSkaterNumber());
               GenerateHtml("obs/current_skater_club", OsisIf->GetCurrentSkaterClub());
               GenerateHtml("obs/current_skater_nation", OsisIf->GetCurrentSkaterNation());

               GenerateSkaterInfoHtml("obs/skater/index.html");
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
               GenerateHtml("obs/event_name", OsisIf->GetEventName());
               GenerateHtml("obs/event_abbreviation", OsisIf->GetEventAbbreviation());
            }
            break;
         case ActionToScene::SEGMENT_START:
            {
               GenerateHtml("obs/segment_name", OsisIf->GetSegmentName());
               GenerateHtml("obs/category_name", OsisIf->GetCategoryName());
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
               GenerateHtml("obs/segment_result_list.html", SegmentResultList);
            }
            break;
         case ActionToScene::CATEGORY_RESULT_LIST:
            {
               QMap<int, QList<QString>> CategoryResultList;
               OsisIf->GetCategoryResultList(CategoryResultList);
               if (CategoryResultList.isEmpty())
               {
                  passToObs = false;
               }
               GenerateHtml("obs/category_result_list.html", CategoryResultList);
            }
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
      QString ext = info.completeSuffix();
      if (info.completeSuffix() == "txt")
      {
         stream.setCodec("UTF-8");
      }
      stream << text << endl;
   }
}

void Actions::GenerateHtml(const QString& fileName, QMap<int, QList<QString> >& outputList)
{
   int i;
   QFileInfo fileInfo(fileName);
   QString outputFile = fileInfo.fileName();
   QString html;
   html  = "<html>";
   html += "<head> <meta http-equiv=\"Content-Type\" content=\"text/html\"> ";
   html += "<META HTTP-EQUIV=\"refresh\" CONTENT=\"5\"; URL=http://localhost:8080/" + outputFile + "\">";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html += "<body class=\"PageBody\">";
   html += "<table width=\"100%\" align=\"center\" border=\"0\" cellspacing=\"1\">";
   for (auto startNum : outputList.keys())
   {
      QList<QString> info = outputList[startNum];
      int columns = info.size();
      if (columns == 0)
      {
         continue;
      }

      html += "<tr class=\"Line1White\">";
      html += "<td>" + QString::number(startNum) + "</td>";
      html += "<td class=\"CellLeft\"><a>" + info[0].toUtf8() + "</a></td>";
      for (i = 1; i < columns; i++)
      {
         html += "<td>" + info[i].toUtf8() + "</td>";
      }
      html += "</tr>";
   }
   html += "</table></body></html>";
   SaveToFile(fileName, html);
}

void Actions::GenerateNewHtmlList(const QString& fileName, QMap<int, QList<QString> >& outputList, const QString& headLine)
{
   int i;
   QFileInfo fileInfo(fileName);
   QString outputFile = fileInfo.fileName();
   float groups = (float)outputList.count() / (float)MAX_LIST_ENTRIES;
   QString html;
   html  = "<!DOCTYPE html>";
   html += "<html><head><link rel=\"stylesheet\" href=\"../css/style" + QString::number(ceil(groups)) +".css\"></head><body>";
   html += "<div class=\"dsu_list_bar\"><img src=\"../img/list.png\"></div>";
   QString categoryName = OsisIf->GetCategoryName();
   html += "<div class=\"dsu_category\"><p>" + categoryName.toUtf8() + "</p></div>";
   QString segmentName = OsisIf->GetSegmentName();
   html += "<div class=\"dsu_segment\"><p>" + headLine + " - " + segmentName.toUtf8() + "</p></div>";
   html += "<div class=\"dsu_slides\"><ul>";

   int entry = 0;
   for (auto startNum : outputList.keys())
   {
       QList<QString> info = outputList[startNum];
       int columns = info.size();
       if (columns == 0)
       {
          continue;
       }

      if (entry == 0)
      {
         html += "<li><div class=\"dsu_list\"><table class=\"dsu_list_table\"><tbody>";
      }

      html += "<tr>";
      html += "<td>" + QString::number(startNum) + "</td>";
      for (i = 0; i < columns; i++)
      {
         if (QString::compare(info[i], "0.00"))
         {
            html += "<td>" + info[i].toUtf8() + "</td>";
         }
         else
         {
            html += "<td></td>";
         }
      }
      html += "</tr>";

      if (entry == MAX_LIST_ENTRIES - 1)
      {
         html += "</tbody></table></div></li>";
         entry = 0;
      }
      else
      {
         entry++;
      }
   }
   if (entry)
   {
      html += "</tbody></table></div></li>";
   }
   html += "</ul></div></body></html>";
   SaveToFile(fileName, html);
}

void Actions::GenerateHtml(const QString& fName, const QString& text)
{
   SaveToFile(fName + ".txt", text.toUtf8());

   QFileInfo fileInfo(fName + ".html");
   QString outputFile = fileInfo.fileName();
   QString html;
   html = "<html>";
   html +="<head> <meta http-equiv=\"Content-Type\" content=\"text/html\"> ";
   html += "<META HTTP-EQUIV=\"refresh\" CONTENT=\"5\"; URL=http://localhost:8080/" + outputFile + "\">";
   html += "<link rel=\"stylesheet\" href=\"fs_info.css\"> </head>";
   html += "<body class=\"PageBody\">";
   html += "<table width=\"100%\" align=\"center\" border=\"0\" cellspacing=\"1\">";
   html += "<tr class=\"Line1White\">";
   html += "<td class=\"CellLeft\"><a>" + text.toUtf8() + "</a></td>";
   html += "</tr></table></body></html>";
   SaveToFile(fName + ".html", html);
}

void Actions::GenerateResultHtml(const QString& fName)
{
    QFileInfo fileInfo(fName);
    QString outputFile = fileInfo.fileName();
    QString html;

    html = "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"../css/style_result.css\"></head><body>";
    html +="<div class=\"dsu_list_bar\"><img src=\"../img/info_bar.png\"></div>";
    html += "<div class=\"dsu_participant_info\">";
    html += "<div class=\"dsu_participant_name\">" + OsisIf->GetCurrentSkaterName().toUtf8() + "</div>";
    html += "<div class=\"dsu_participant_club\">" + OsisIf->GetCurrentSkaterNation() + " " + OsisIf->GetCurrentSkaterClub() + "</div>";
    html += "<div id=\"score-animation-3\" class=\"dsu_rank\">" + OsisIf->GetTRank() + "</div>";
    html += "</div><div class=\"dsu_participant_score\">";
    html += "<div class=\"dsu_tes\"></div><div class=\"dsu_tes_score\">" + OsisIf->GetTES() + "</div>";
    html += "<div class=\"dsu_tcs\"></div><div class=\"dsu_tcs_score\">" + OsisIf->GetTCS() + "</div>";
    html += "<div class=\"dsu_ded\"></div><div class=\"dsu_ded_value\">" + OsisIf->GetDeduction() + "</div>";
    if (!QString::compare(OsisIf->GetSegmentAbbreviation(), "SP"))
    {
       html += "<div id=\"score-animation-1\" class=\"dsu_short_program\"></div>";
       html += "<div id=\"score-animation-1\" class=\"dsu_segment_score\">" + OsisIf->GetPoints() + "</div>";
    }
    else
    {
       html += "<div id=\"score-animation-1\" class=\"dsu_free_program\"></div>";
       html += "<div id=\"score-animation-1\" class=\"dsu_segment_score\">" + OsisIf->GetPoints() + "</div>";
       html += "<div id=\"score-animation-2\"  class=\"dsu_total\"></div>";
       html += "<div id=\"score-animation-2\"  class=\"dsu_total_score\">" + OsisIf->GetTPoints() + "</div>";
    }
    html += "</div></body></html>";
    SaveToFile(fName, html);
}

void Actions::GenerateSkaterInfoHtml(const QString& fName)
{
    QFileInfo fileInfo(fName);
    QString outputFile = fileInfo.fileName();
    QString html;

    html = "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"../css/style_name.css\"></head><body>";
    html +="<div class=\"dsu_list_bar\"><img src=\"../img/info_bar.png\"></div>";
    html += "<div class=\"dsu_info_table_participant\">";
    html += "<table class=\"dsu_participant_data\"><tr>";
    html += "<td>" + OsisIf->GetCurrentSkaterNumber() + "</td>";
    html += "<td>" + OsisIf->GetCurrentSkaterNation() + " " + OsisIf->GetCurrentSkaterClub() + "</td>";
    html += "<td>" + OsisIf->GetCurrentSkaterName().toUtf8() + "</td></tr></table></div>";
    html += "<div class=\"dsu_info_table_info\">";
    html += "<table class=\"dsu_participant_group\"><tr>";
    html += "<td>" + OsisIf->GetCategoryName().toUtf8() + "</td>";
    html += "<td>" + OsisIf->GetSegmentName().toUtf8() + "</td>";
    if (QString::compare(OsisIf->GetSegmentAbbreviation(), "SP") && QString::compare(OsisIf->GetTPoints(),"0.00"))
    {
        html += "<td>Short Program</td><td>" + OsisIf->GetTPoints() + "</td>";
    }
    html += "</tr></table></div></body></html>";
    SaveToFile(fName, html);
}

void Actions::GenerateEventInfoHtml(const QString& fName)
{
    QFileInfo fileInfo(fName);
    QString outputFile = fileInfo.fileName();
    QString html;

    html = "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"../css/style_event.css\"></head><body>";
    html +="<div class=\"dsu_list_bar\"><img src=\"../img/info_bar.png\"></div>";
    html += "<div class=\"dsu_event_type\"></div>";
    html += "<div class=\"dsu_event_info\"><div class=\"dsu_category\">" + OsisIf->GetCategoryName().toUtf8() + "</div>";
    html += "<div class=\"dsu_segment\">" + OsisIf->GetSegmentName().toUtf8() + "</div></div></body></html>";
    SaveToFile(fName, html);
}
