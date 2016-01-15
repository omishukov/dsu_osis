/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include "trace.h"

QTextStream *out = 0;

bool logopt[4] = {false, false, false, false}; // data, error, warning

void logOutput(QtMsgType type, const QMessageLogContext &/*context*/, const QString &msg)
{
   bool enablePrint = false;
   QString debugdate = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
   switch (type)
   {
      case QtDebugMsg:
         if (logopt[LOG_DEBUG])
         {
            debugdate += " [D]:";
            enablePrint = true;
         }
         break;
      case QtWarningMsg:
         if (logopt[LOG_WARN])
         {
            debugdate += " [W]:";
            enablePrint = true;
         }
         break;
      case QtCriticalMsg:
         if (logopt[LOG_ERROR])
         {
            debugdate += " [C]:";
            enablePrint = true;
         }
         break;
      case QtFatalMsg:
         debugdate += " [F]:";
         enablePrint = true;
         break;
      case QtInfoMsg:
         if (logopt[LOG_DATA])
         {
            debugdate += " [I]:";
            enablePrint = true;
         }
         break;
   }

   if (enablePrint)
   {
      (*out) << debugdate << " " << msg << endl;
   }
}

int main(int argc, char *argv[])
{
   QString fileName = argv[0];
   fileName.replace(".exe", ".log");
   QFile *log = new QFile(fileName);
   if (log->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
   {
      out = new QTextStream(log);
   }
   qInstallMessageHandler(logOutput);

   QApplication a(argc, argv);
   MainWindow w(log->fileName());
   w.show();

   bool res = a.exec();

   qInstallMessageHandler(0);
   if (out)
   {
      delete out;
   }
   log->close();
   delete log;

   return res;
}

// Backlog
#if 0
* Min windows size (do not hide basic GUI elements by resizing)
* Use QSettings (ip-addr, mode, other parameters). Save/Restore
* Create Icon
#endif
