#include <QApplication>
#include <QPushButton>
#include <ui/userinterface.h>
#include <configuration.h>
#include "link/osislink.h"
#include "link/obslink.h"

void SetupLog(QString& fName);
void CloseLog();

const QString IsuCalcFsGroupName = "IsuCalcFs";
const QString ObsGroupName = "OBS";

int main(int argc, char **argv)
{
   QString fileName = argv[0];
   SetupLog(fileName);

   QApplication app (argc, argv);

   QString configFileName = argv[0];
   configFileName.replace(".exe", ".ini");
   Configuration app_Config(configFileName);

   OsisLink osisLink(IsuCalcFsGroupName, app_Config);
   ObsLink obsLink(ObsGroupName, app_Config);
   osisLink.Start();
   obsLink.Start();

   UserInterface ui(osisLink, obsLink);
   ui.setFixedSize(800, 600);
   ui.show();

   int res = app.exec();

   osisLink.Stop();
   obsLink.Stop();
   CloseLog();

   return res;
}
