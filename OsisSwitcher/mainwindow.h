#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "isucalclink.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private:
   void InitIsuCalcLink();

   Ui::MainWindow *ui;
   DataQueue DataIf;
   IsuCalcLink CalcLink;
   QThread CalcLinkThread;
};

#endif // MAINWINDOW_H
