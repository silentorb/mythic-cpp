#include "Scene_Flower.h"
#include "scenery/Scene.h"
#include "perspective/Viewport.h"

namespace bloom {

  Scene_Flower::Scene_Flower(Garden &garden, shared_ptr<scenery::Scene> &scene, Flower *parent) :
    scene(scene),
    Flower(garden, parent) {

  }

  void Scene_Flower::render() {
    Flower::render();
    auto bounds = get_bounds();
    auto pos = bounds.get_position();
    auto position = converter.convert(vec2(pos.x, 1000 - bounds.get_corner().y));
    auto dimensions = converter.convert(bounds.get_dimensions());

    scene->get_viewport().set_bounds(position, dimensions);
    scene->render();
  }
}
