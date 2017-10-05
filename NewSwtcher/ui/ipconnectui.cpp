#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QIntValidator>
#include <QDialogButtonBox>
#include "ipconnectui.h"

IpConnectUi::IpConnectUi(Configuration &config, const QString &group, QWidget *parent)
   : QWidget(parent)
   , qs_GroupBoxName(group)
   , ipConfig(config)
{
   qgb_IsuCalcFsConnect = new QGroupBox(qs_GroupBoxName);

   if (ipConfig.GetIpInfo(qs_GroupBoxName, IpAddress, IpPort) == false)
   {
      IpAddress = "127.0.0.1";
      IpPort = "4000";
   }

   ql_IpAddressPort = new QLabel(IpAddress + ":" + IpPort);
   ql_IpStatus = new QLabel("Disconnected");
   ql_IpStatus->setMaximumWidth(80);
   ql_IpStatus->setStyleSheet("border: 1px solid");
   qpb_Edit = new QPushButton("...");
   qpb_Edit->setMaximumWidth(20);
   connect(qpb_Edit, SIGNAL (released()), this, SLOT (editButton()));
   qpb_Connect = new QPushButton("Connect");
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

void IpConnectUi::editButton()
{
   ChangeIpInfo dialog(IpAddress, IpPort, this);
   if(dialog.exec() == QDialog::Accepted)
   {
     QString ipAddr;
     QString ipPort;
     dialog.GetIpInfo(ipAddr, ipPort);
     ql_IpAddressPort->setText(ipAddr + " : " + ipPort );
   }
}

void IpConnectUi::connectButton()
{

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
