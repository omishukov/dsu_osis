#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

QString inifile = "osisproxy.ini";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , CalcIpValidator(0)
    , PortValidator(0)
{
    ui->setupUi(this);

    setIpValitation();

    readSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();

    delete ui;
    delete CalcIpValidator;
    delete PortValidator;
}

void MainWindow::setIpValitation()
{
   // Setup validating for the IP-address input
   QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
   QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
   CalcIpValidator = new QRegExpValidator(ipRegex, this);
   ui->IsuCalcIP_LE->setValidator(CalcIpValidator);

   PortValidator = new QIntValidator(6,65535,this);// 0 to 65535
   ui->IsuCalcPort_LE->setValidator(PortValidator);//ports
   ui->ProxyServerPort_LE->setValidator(PortValidator);//ports
}

void MainWindow::readSettings()
{
    QSettings settings(inifile, QSettings::IniFormat);

    settings.beginGroup("Connection");
    ui->IsuCalcIP_LE->setText(settings.value("isu_calc_ip", "127.0.0.1").toString());
    ui->IsuCalcPort_LE->setText(settings.value("isu_calc_port", "4000").toString());
    ui->Reconnect_CB->setCheckState(settings.value("isu_calc_recon", false).toBool()?Qt::Checked:Qt::Unchecked);
    ui->ProxyServerPort_LE->setText(settings.value("proxy_server_port", "5000").toString());
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings(inifile, QSettings::IniFormat);

    settings.beginGroup("Connection");
    settings.setValue("isu_calc_ip", ui->IsuCalcIP_LE->text());
    settings.setValue("isu_calc_port", ui->IsuCalcPort_LE->text());
    settings.setValue("isu_calc_recon", ui->Reconnect_CB->checkState());
    settings.setValue("proxy_server_port", ui->ProxyServerPort_LE->text());
    settings.endGroup();

}

