#ifndef ISUCALCFSCONNECTUI_H
#define ISUCALCFSCONNECTUI_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <configuration.h>

class IpConnectUi : public QWidget
{
   Q_OBJECT
public:
   explicit IpConnectUi(Configuration& config, const QString& group, QWidget *parent = nullptr);

signals:

public slots:
   void editButton();
   void connectButton();

private:
   const QString qs_GroupBoxName;
   QGroupBox* qgb_IsuCalcFsConnect;
   QLabel* ql_IpAddressPort;
   QLabel* ql_IpStatus;
   QPushButton* qpb_Edit;
   QPushButton* qpb_Connect;
   QString IpAddress;
   QString IpPort;


   Configuration& ipConfig;
};

class ChangeIpInfo : public QDialog
{
   Q_OBJECT
public:
   explicit ChangeIpInfo(const QString& ipAddr, const QString& ipPort, QWidget *parent);
   void GetIpInfo(QString &ipAddr, QString& ipPort);

private:
   QLineEdit* qle_IpAddr;
   QLineEdit* qle_IpPort;
};

#endif // ISUCALCFSCONNECTUI_H
