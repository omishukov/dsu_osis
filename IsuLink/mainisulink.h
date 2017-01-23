#ifndef MAINISULINK_H
#define MAINISULINK_H

#include <QMainWindow>

namespace Ui {
   class IsuLinkMain;
}

class IsuLinkMain : public QMainWindow
{
   Q_OBJECT

public:
   explicit IsuLinkMain(QWidget *parent = 0);
   ~IsuLinkMain();

private:
   Ui::IsuLinkMain *ui;
};

#endif // MAINISULINK_H
