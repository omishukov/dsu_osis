#ifndef CALCFSSTATUSUI_H
#define CALCFSSTATUSUI_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>

class CalcFsStatusUi : public QWidget
{
   Q_OBJECT
public:
   explicit CalcFsStatusUi(QWidget *parent = nullptr);

signals:

public slots:

private:
   QGroupBox* qgb_IsuCalcFsInfo;

};

#endif // CALCFSSTATUSUI_H
