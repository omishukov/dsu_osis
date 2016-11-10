#ifndef SCENEDATA_H
#define SCENEDATA_H

#include <QObject>
#include <osisif.h>

class SceneData : public QObject
{
   Q_OBJECT
public:
   explicit SceneData(SwitcherOsisIf* ObsIf, QObject *parent = 0);

   enum ObsSceneData
   {
      current_action,
      points,
      tes,
      tcs,
      bonus,
      deduction,
      rank,
      segment_result_list,
      category_result_list,
      current_skater,
      current_start_number,
      current_skater_club,
      current_skater_nation,
      starting_order,
      current_warmup_group,
      current_warmup_group_number,
      event_name,
      event_abbreviation,
      segment_name,
      category_name,
      scene_name,
      scene_score,
      scene_event,
      scene_starting_order,
      scene_standings,
      scene_result,
      scene_warm_up
   };
   Q_ENUM(ObsSceneData)

   void Save(ObsSceneData type, QString& data);
   void Save(ObsSceneData type, QMap<int, QList<QString> >& outputList);
   bool GenerateFiles(); // Returns true if has next page
signals:

public slots:

private:
   SwitcherOsisIf* obsIf;
};

#endif // SCENEDATA_H
