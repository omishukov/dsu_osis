#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>

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
    Ui::MainWindow *ui;

    void setIpValitation();
    void readSettings();
    void saveSettings();


    QValidator* CalcIpValidator;
    QValidator* PortValidator;
};

#endif // MAINWINDOW_H
