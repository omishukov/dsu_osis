#ifndef ISUCALCFSCONNECTUI_H
#define ISUCALCFSCONNECTUI_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QMetaEnum>
#include <link/linkif.h>
#include <ui/uilinkif.h>

class IpConnectUi : public QWidget, public UiLinkIf
{
   Q_OBJECT
public:
   explicit IpConnectUi(LinkIf& linkIf, QWidget *parent = nullptr);

   typedef enum ConnectionButtonAction
   {
      Connect,
      Disconnect
   } QPB_ConnectionAction;
   Q_ENUM(ConnectionButtonAction)

   typedef enum ConnectionLabelState
   {
      Disconnected,
      Disconnecting,
      Connecting,
      Connected
   } QL_ConnectionState;
   Q_ENUM(ConnectionLabelState)

   void LinkConnected();
   void LinkDisconnected();

signals:

public slots:
   void editButton();
   void connectButton();

private:
   void ChangeConnectionButton(QPB_ConnectionAction newAction);
   void ChangeConnectionState(QL_ConnectionState newState);

private:
   const QString qs_GroupBoxName;
   QGroupBox* qgb_IsuCalcFsConnect;
   QLabel* ql_IpAddressPort;
   QLabel* ql_IpStatus;
   QPushButton* qpb_Edit;
   QPushButton* qpb_Connect;
   QString IpAddress;
   QString IpPort;
   LinkIf& link_IF;
   QPB_ConnectionAction qpb_ConnectionAction;
   QL_ConnectionState ql_ConnectionState;
   QMetaEnum qme_ConnectionAction;
   QMetaEnum qme_ConnectionState;
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
