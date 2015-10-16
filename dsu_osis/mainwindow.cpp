#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegExpValidator>
#include <QSettings>

const QString organization = "DSU";
const QString application = "Open Scoring Interface Controller";

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   setIpValitation();
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::setIpValitation()
{
   // Setup validating for the IP-address input
   QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
   QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
   QValidator *ipValidator = new QRegExpValidator(ipRegex, this);
   ui->IPv4Address->setValidator(ipValidator);
}

void MainWindow::readSettings()
{
   QSettings settings(organization, application);

}
