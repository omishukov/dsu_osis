#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QMap>
#include "actions.h"

Actions::Actions(QObject* parent)
   : QObject(parent)
   , MetaActionsEnum(QMetaEnum::fromType<ObsAction>())
{
}

void Actions::DoActions()
{
   if (!OsisIf)
   {
      return;
   }

   bool passToObs;
   foreach(int action, ActionList)
   {
      QString actionName = MetaActionsEnum.valueToKey(action);
      SaveToFile("obs/current_action.txt", actionName);

      passToObs = true;
      switch (action)
      {
         case ACTION_1SC:
            break;
         case ACTION_1S1:
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
         case ACTION_1S2:
            {
               // Save rank from Performance
               SaveToFile("obs/current_participant_rank.txt", OsisIf->GetRank());

               // Segment Result list
               QMap<int, QList<QString>> SegmentResultList;
               OsisIf->GetSegmentResultList(SegmentResultList);
               GenerateSegmentResultListHtml(SegmentResultList);
            }
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
               SaveToFile("obs/current_skater.txt", OsisIf->GetCurrentSkaterName());
               SaveToFile("obs/current_start_number.txt", OsisIf->GetCurrentSkaterNumber());
               SaveToFile("obs/current_skater_club.txt", OsisIf->GetCurrentSkaterClub());
               SaveToFile("obs/current_skater_nation.txt", OsisIf->GetCurrentSkaterNation());

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
               SaveToFile("obs/current_skater.txt", OsisIf->GetCurrentSkaterName());
               SaveToFile("obs/current_start_number.txt", OsisIf->GetCurrentSkaterNumber());
               SaveToFile("obs/current_skater_club.txt", OsisIf->GetCurrentSkaterClub());
               SaveToFile("obs/current_skater_nation.txt", OsisIf->GetCurrentSkaterNation());
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
            SaveToFile("obs/event_name.txt", OsisIf->GetEventName());
            break;
         case SEGMENT_START:
            {
            SaveToFile("obs/segment_name.txt", OsisIf->GetSegmentName());
            SaveToFile("obs/category_name.txt", OsisIf->GetCategoryName());
            }
            break;
         case PRF_RANKING:
            break;
         case SEGMENT_RESULT_LIST:
            // Generate HTML Table with Segment result
            break;
         case CATEGORY_RESULT_LIST:
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
   if (action > NO_ACTIONS && action < LAST_ACTION)
   {
      ActionList.push_back(action);
   }
}

void Actions::SetObsIf(QObject* _obsIf)
{
   ObsIf = _obsIf;
   //connect(this, SIGNAL(SendOsisEvent(int)), ObsIf, SLOT(HandleEvent(int)));
}

QString Actions::GetActionName(int action)
{
   if (action > NO_ACTIONS && action < LAST_ACTION)
   {
      return MetaActionsEnum.valueToKey(action);
   }
   return QString();
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
