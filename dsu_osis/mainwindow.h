#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_ClientServerCB_activated(int index);

private:
   void loadConnectionSettings();
   void setIpValitation();
   void readSettings();
   void writeSettings();

private:
   Ui::MainWindow *ui;
   typedef enum
   {
      CLIENT,
      SERVER
   } ConnectAs;

   ConnectAs ConnectionType;
   QString IpAddress;
   QString IpPort;
};

#endif // MAINWINDOW_H
