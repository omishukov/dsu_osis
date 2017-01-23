#include "mainisulink.h"
#include "ui_mainisulink.h"

IsuLinkMain::IsuLinkMain(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::IsuLinkMain)
{
   ui->setupUi(this);
}

IsuLinkMain::~IsuLinkMain()
{
   delete ui;
}
