#include <QApplication>
#include <QPushButton>
#include <ui/userinterface.h>
#include <configuration.h>

int main(int argc, char **argv)
{
   QApplication app (argc, argv);

   QString configFileName = argv[0];
   configFileName.replace(".exe", ".ini");
   Configuration app_Config(configFileName);

   UserInterface ui(app_Config);
   ui.setFixedSize(800, 600);
   ui.show();

   return app.exec();
}
