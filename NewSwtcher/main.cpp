#include <QApplication>
#include <QPushButton>
#include <ui/userinterface.h>
#include <configuration.h>
#include <link/osislink.h>
#include <link/obslink.h>
#include <osis/dataqueue.h>
#include <osis/parser.h>

void SetupLog(QString& fName);
void CloseLog();

const QString IsuCalcFsGroupName = "IsuCalcFs";
const QString ObsGroupName = "OBS";

int main(int argc, char **argv)
{
   QString fileName = argv[0];
   SetupLog(fileName);


   QApplication app(argc, argv);

   QString configFileName = argv[0];
   configFileName.replace(".exe", ".ini");
   Configuration app_Config(configFileName);

   DataQueue osisDataQueue;

   OsisParser osisParser(&osisDataQueue);
   OsisLink osisLink(IsuCalcFsGroupName, app_Config, &osisDataQueue);
   ObsLink obsLink(ObsGroupName, app_Config);
   osisParser.Start();
   osisLink.Start();
   obsLink.Start();

   UserInterface ui(osisLink, obsLink);
   osisLink.SetUiIf(ui.GetOsisLinkIf());
   obsLink.SetUiIf(ui.GetObsLinkIf());
//   ui.setFixedSize(800, 600);
   ui.show();

   int res = app.exec();

   osisLink.SetUiIf(0);
   obsLink.SetUiIf(0);

   osisLink.Stop();
   osisParser.Stop();
   obsLink.Stop();
   CloseLog();

   return res;
}
