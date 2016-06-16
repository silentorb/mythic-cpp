#include <lookinglass/House.h>
#include "Scene_Flower.h"
#include "scenery/Scene.h"
#include "perspective/Viewport.h"
#include "bloom/Garden.h"

namespace bloom {

  Scene_Flower::Scene_Flower(Garden &garden, shared_ptr<scenery::Scene> scene, Flower_Old *parent) :
    scene(scene),
    Flower_Old(garden, parent) {
  }

  Scene_Flower::Scene_Flower(Garden &garden, Flower_Old *parent) :
    Scene_Flower(garden, shared_ptr<scenery::Scene>(new scenery::Scene(lookinglass::House::get_instance())), parent) {

  }

  void Scene_Flower::render() {
    Flower_Old::render();
    auto bounds = get_inner_bounds();
    auto pos = bounds.get_position();
    auto position = converter.convert_to_pixels(vec2(pos.x, converter.get_unit_dimensions().y - bounds.get_corner().y));
    auto dimensions = converter.convert_to_pixels(bounds.get_dimensions());

    scene->get_viewport().set_bounds(position, dimensions);

    garden.get_draw().enable_3d(true);
    scene->render();
    garden.get_draw().enable_3d(false);
  }
}
