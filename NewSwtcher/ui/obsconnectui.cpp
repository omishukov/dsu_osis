#include <QHBoxLayout>
#include <QVBoxLayout>
#include "obsconnectui.h"

ObsConnectUi::ObsConnectUi(QWidget *parent) : QWidget(parent)
{
   qgb_ObsConnect = new QGroupBox("OBS");

   ql_IpAddress = new QLabel("127.0.0.1");
   ql_IpPort = new QLabel("4444");

   QHBoxLayout *connectionLayout = new QHBoxLayout;
   connectionLayout->addWidget(ql_IpAddress);
   connectionLayout->addWidget(ql_IpPort);

   QVBoxLayout *configLayout = new QVBoxLayout;
   configLayout->addLayout(connectionLayout);
   qgb_ObsConnect->setLayout(configLayout);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(qgb_ObsConnect);
   mainLayout->addStretch(1);
   setLayout(mainLayout);
}
