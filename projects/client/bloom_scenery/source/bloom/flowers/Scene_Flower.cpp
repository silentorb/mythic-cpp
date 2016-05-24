#include "Scene_Flower.h"
#include "scenery/Scene.h"
#include "perspective/Viewport.h"
#include "bloom/Garden.h"

namespace bloom {

  Scene_Flower::Scene_Flower(Garden &garden, shared_ptr<scenery::Scene> scene, Flower *parent) :
    scene(scene),
    Flower(garden, parent) {
		debug_id = 32;
  }

  Scene_Flower::Scene_Flower(Garden &garden, Flower *parent) :
    Scene_Flower(garden, shared_ptr<scenery::Scene>(new scenery::Scene(garden.get_house())), parent) {

  }

  void Scene_Flower::render() {
    Flower::render();
    auto bounds = get_outer_bounds();
    auto pos = bounds.get_position();
    auto position = converter.convert_to_pixels(vec2(pos.x, converter.get_unit_dimensions().y - bounds.get_corner().y));
    auto dimensions = converter.convert_to_pixels(bounds.get_dimensions());

    scene->get_viewport().set_bounds(position, dimensions);

    garden.enable_3d(true);
    scene->render();
    garden.enable_3d(false);
  }
}
