#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   InitIsuCalcLink();
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::InitIsuCalcLink()
{
   CalcLink.SetDataIf(&DataIf);
   CalcLink.moveToThread(&CalcLinkThread);

}
