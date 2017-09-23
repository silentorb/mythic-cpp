#include "Scene_Manager.h"
#include "through/create_mist.h"
#include "glow_gl.h"

using namespace std;

namespace scenery {

  Scene_Manager::Scene_Manager() :
    lighting(new Lighting_Data()) {

    lighting->count = 0;

    auto scene_definition = new Struct_Info(2, "Lighting", {
			{"count", Field_Type::integer},
    });
    lighting_mist = unique_ptr<Mist<Lighting_Data>>(
      create_mist<Lighting_Data>(scene_definition));
  }

  void Scene_Manager::update_lights() {
    lighting_mist->update(lighting.get());
  }

  void Scene_Manager::update() {
    update_lights();
  }

  Light_Data &Scene_Manager::add_light() {
    lighting->count++;
    Light_Data *light = &lighting->lights[lighting->count - 1];
    memset(light, 0, sizeof(Light_Data));
    return *light;
  }
}