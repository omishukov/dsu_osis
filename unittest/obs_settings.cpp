#include <osis_unittest.h>


void UnittestTest::ObsParseGlobalIni()
{
   QSettings settings(QSettings::IniFormat, QSettings::UserScope, "obs-studio", "global");
   QString SceneFile = settings.value("Basic/SceneCollectionFile").toString();
   qDebug() << "QBS Scene file " << SceneFile << ".json" << endl;

}
