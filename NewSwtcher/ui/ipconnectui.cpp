#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QDialogButtonBox>
#include "ipconnectui.h"

IpConnectUi::IpConnectUi(LinkIf &linkIf, QWidget *parent)
   : QWidget(parent)
   , qs_GroupBoxName(linkIf.GetGroupName())
   , link_IF(linkIf)
   , qpb_ConnectionAction(Connect)
   , ql_ConnectionState(Disconnected)
   , qme_ConnectionAction(QMetaEnum::fromType<ConnectionButtonAction>())
   , qme_ConnectionState(QMetaEnum::fromType<ConnectionLabelState>())
{
   qgb_IsuCalcFsConnect = new QGroupBox(qs_GroupBoxName);

   link_IF.GetIpInfo(IpAddress, IpPort);

   ql_IpAddressPort = new QLabel(IpAddress + " : " + IpPort);
   ql_IpAddressPort->setAlignment(Qt::AlignCenter);
   ql_IpStatus = new QLabel(qme_ConnectionState.valueToKey(ql_ConnectionState));
   ql_IpStatus->setMaximumWidth(80);
   ql_IpStatus->setStyleSheet("border: 1px solid");
   ql_IpStatus->setAlignment(Qt::AlignCenter);

   qpb_Edit = new QPushButton("...");
   qpb_Edit->setMaximumWidth(20);
   connect(qpb_Edit, SIGNAL (released()), this, SLOT (editButton()));

   qpb_Connect = new QPushButton(qme_ConnectionAction.valueToKey(qpb_ConnectionAction));
   connect(qpb_Connect, SIGNAL (released()), this, SLOT (connectButton()));

   QHBoxLayout *connectionLayout = new QHBoxLayout;
   connectionLayout->addWidget(ql_IpAddressPort);
   connectionLayout->addWidget(qpb_Edit);
   connectionLayout->addWidget(ql_IpStatus);
   connectionLayout->addWidget(qpb_Connect);

   QVBoxLayout *configLayout = new QVBoxLayout;
   configLayout->addLayout(connectionLayout);
   qgb_IsuCalcFsConnect->setLayout(configLayout);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(qgb_IsuCalcFsConnect);
   mainLayout->addStretch(1);
   setLayout(mainLayout);
}

void IpConnectUi::LinkConnected()
{
   ChangeConnectionState(Connected);
   ChangeConnectionButton(Disconnect);
}

void IpConnectUi::LinkDisconnected()
{
   if (ql_ConnectionState == Disconnecting)
   {
      ChangeConnectionState(Disconnected);
      ChangeConnectionButton(Connect);
   }
   else
   {
      ChangeConnectionState(Connecting);
   }
}

void IpConnectUi::editButton()
{
   // TODO: Disable Edit button in "Connected" state

   ChangeIpInfo dialog(IpAddress, IpPort, this);
   if(dialog.exec() == QDialog::Accepted)
   {
      QString ipAddr;
      QString ipPort;
      dialog.GetIpInfo(ipAddr, ipPort);
      if (QString::compare(IpAddress, ipAddr) || QString::compare(IpPort, ipPort))
      {
         IpAddress = ipAddr;
         IpPort = ipPort;
         link_IF.SaveIpInfo(IpAddress, IpPort);
         ql_IpAddressPort->setText(IpAddress + " : " + IpPort );
      }
   }
}

void IpConnectUi::connectButton()
{
   switch (qpb_ConnectionAction) {
   case Connect:
      {
         link_IF.Connect();
         ChangeConnectionButton(Disconnect);
         ChangeConnectionState(Connecting);
      }
      break;
   case Disconnect:
      {
         link_IF.Disconnect();
         ChangeConnectionButton(Connect);
         ChangeConnectionState(Disconnecting);
      }
      break;
   }
}

void IpConnectUi::ChangeConnectionButton(IpConnectUi::QPB_ConnectionAction newAction)
{
   qpb_ConnectionAction = newAction;
   qpb_Connect->setText(qme_ConnectionAction.valueToKey(qpb_ConnectionAction));
}

void IpConnectUi::ChangeConnectionState(IpConnectUi::QL_ConnectionState newState)
{
   ql_ConnectionState = newState;
   ql_IpStatus->setText(qme_ConnectionState.valueToKey(ql_ConnectionState));
}

ChangeIpInfo::ChangeIpInfo(const QString &ipAddr, const QString &ipPort, QWidget *parent)
   : QDialog(parent)
{
   QLabel* labelIpAddr = new QLabel("IP Address:");
   qle_IpAddr = new QLineEdit(ipAddr);
   QLabel* labelIpPort = new QLabel("Port:");
   qle_IpPort = new QLineEdit(ipPort);

   QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

   connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
   connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

   // Setup validating for the IP-address input
   QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
   QRegExp ipRegex ("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$");
   QValidator *validatorIpAddr = new QRegExpValidator(ipRegex, this);
   qle_IpAddr->setValidator(validatorIpAddr);

   QValidator *validatorIpPort = new QIntValidator(6,65535,this);// 0 to 65535
   qle_IpPort->setValidator(validatorIpPort);//ports

   QHBoxLayout *connectionLayout = new QHBoxLayout;
   connectionLayout->addWidget(labelIpAddr);
   connectionLayout->addWidget(qle_IpAddr);
   connectionLayout->addWidget(labelIpPort);
   connectionLayout->addWidget(qle_IpPort);

   QVBoxLayout *configLayout = new QVBoxLayout;
   configLayout->addLayout(connectionLayout);
   configLayout->addWidget(buttonBox);

   setLayout(configLayout);
}

void ChangeIpInfo::GetIpInfo(QString &ipAddr, QString &ipPort)
{
   ipAddr = qle_IpAddr->text();
   ipPort = qle_IpPort->text();
}
