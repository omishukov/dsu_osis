#include "mainisulink.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   IsuLinkMain w;
   w.show();

   return a.exec();
}
