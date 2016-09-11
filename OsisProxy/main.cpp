#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QFile>

QTextStream *out = 0;
QFile *logfile = 0;

void logOutput(QtMsgType type, const QMessageLogContext &/*context*/, const QString &msg)
{
   bool enablePrint = false;
   QString debugdate = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
   switch (type)
   {
      case QtDebugMsg:
         {
            debugdate += " [D]:";
            enablePrint = true;
         }
         break;
      case QtWarningMsg:
         {
            debugdate += " [W]:";
            enablePrint = true;
         }
         break;
      case QtCriticalMsg:
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
         {
            debugdate += " [I]:";
            enablePrint = true;
         }
         break;
   }

//   if (enablePrint && out && logfile)
   {
      (*out) << debugdate << " [" << msg << "]" << endl;
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

   int ret = a.exec();

   qInstallMessageHandler(0);
   if (out)
   {
      out->flush();
      logfile->flush();
      delete out;
   }
   logfile->close();
   delete logfile;

   return ret;
}
