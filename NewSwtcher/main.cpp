#include <QApplication>
#include <QPushButton>
#include <ui/userinterface.h>
#include <configuration.h>

void SetupLog(QString& fName);
void CloseLog();

int main(int argc, char **argv)
{
   QString fileName = argv[0];
   SetupLog(fileName);

   QApplication app (argc, argv);

   QString configFileName = argv[0];
   configFileName.replace(".exe", ".ini");
   Configuration app_Config(configFileName);

   UserInterface ui(app_Config);
   ui.setFixedSize(800, 600);
   ui.show();

   int res = app.exec();

   CloseLog();

   return res;
}
