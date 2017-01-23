#ifndef MAINISULINK_H
#define MAINISULINK_H

#include <QMainWindow>
#include "dataqueue.h"
#include "isucalclink.h"

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

   DataQueue m_IsuData;
   IsuCalcLink m_CalcTcpClient;
};

#endif // MAINISULINK_H
