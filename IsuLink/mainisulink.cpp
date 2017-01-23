#include "mainisulink.h"
#include "ui_mainisulink.h"
#include <QDebug>

IsuLinkMain::IsuLinkMain(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::IsuLinkMain),
   m_CalcTcpClient(&m_IsuData)
{
   ui->setupUi(this);

   QString version(GIT_VERSION);
   setWindowTitle("IsuLink " + version);

   qDebug() << "Start IsuLink";

}

IsuLinkMain::~IsuLinkMain()
{
   delete ui;
}
