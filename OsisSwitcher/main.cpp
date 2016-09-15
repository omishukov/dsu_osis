/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Contributor(s):
 *   Oleksander Mishukov <dsu@mishukov.dk> */

#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include "trace.h"

static QTextStream *out = 0;
static QFile *logfile = 0;

static bool logopt[4] = {false, false, false, false}; // data, error, warning, debug

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
      out->flush();
      logfile->flush();
   }
}

int main(int argc, char *argv[])
{
   QString fileName = argv[0];
   fileName.replace(".exe", ".log");
   logfile = new QFile(fileName);
   if (logfile->open(QIODevice::Append | QIODevice::Text))
   {
      out = new QTextStream(logfile);
   }
   qInstallMessageHandler(logOutput);

   QApplication a(argc, argv);
   MainWindow w;
   w.show();

   bool res = a.exec();

   qInstallMessageHandler(0);
   if (out)
   {
      delete out;
   }
   logfile->close();
   delete logfile;

   return res;
}
