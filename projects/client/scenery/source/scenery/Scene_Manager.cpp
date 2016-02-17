#include "Scene_Manager.h"
#include "lookinglass/through/create_mist.h"
#include <lookinglass/House.h>

namespace scenery {

  Scene_Manager::Scene_Manager(lookinglass::House &house) {
    auto scene_definition = new Struct_Info(1, "", {
      new Field_Info("view", Field_Type::matrix),
      new Field_Info("projection", Field_Type::matrix),
      new Field_Info("camera_direction", Field_Type::vector3)
    });
    lighting_mist = unique_ptr<Mist<Lighting_Data>>(
      create_mist<Lighting_Data>(scene_definition, house.get_capabilities()));
  }
}