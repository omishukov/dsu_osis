#include <QDateTime>
#include <QMutex>
#include <QTextStream>
#include <QFile>
#include <QLoggingCategory>

const int LOG_DATA = 0;
const int LOG_ERROR = 1;
const int LOG_WARN = 2;
const int LOG_DEBUG = 3;

static bool logopt[4] = {true, true, true, true}; // data, error, warning, debug
static QMutex Mutex;

static QTextStream *out = 0;
static QFile *logfile = 0;

void logOutput(QtMsgType type, const QMessageLogContext &/*context*/, const QString &msg)
{
   QMutexLocker lock(&Mutex);

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

void SetupLog(QString& fName)
{
   QString fileName = fName;
   fileName.replace(".exe", ".log");
   logfile = new QFile(fileName);
   if (logfile->open(QIODevice::Append | QIODevice::Text))
   {
      out = new QTextStream(logfile);
   }
   qInstallMessageHandler(logOutput);

   QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
}

void CloseLog()
{
   qInstallMessageHandler(0);
   if (out)
   {
      delete out;
   }
   logfile->close();
   delete logfile;
}
