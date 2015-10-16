#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   MainWindow w;
   w.show();

   return a.exec();
}

// Backlog
#if 0
* Min windows size (do not hide basic GUI elements by resizing)
* Use QSettings (ip-addr, mode, other parameters). Save/Restore
* Create Icon
#endif
