#ifndef OBSCONNECTUI_H
#define OBSCONNECTUI_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>

class ObsConnectUi : public QWidget
{
   Q_OBJECT
public:
   explicit ObsConnectUi(QWidget *parent = nullptr);

signals:

public slots:

private:
   QGroupBox* qgb_ObsConnect;
   QLabel* ql_IpAddress;
   QLabel* ql_IpPort;
};

#endif // OBSCONNECTUI_H
