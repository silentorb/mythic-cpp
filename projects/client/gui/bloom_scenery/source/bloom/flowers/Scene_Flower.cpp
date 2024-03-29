#include <lookinglass/House.h>
#include <bloom/flowers/Parent_Implementation.h>
#include "Scene_Flower.h"
#include "scenery/Scene.h"
#include "perspective/Viewport.h"
#include "bloom/Garden.h"

namespace bloom {
  namespace flowers {

    Scene_Flower::Scene_Flower(shared_ptr<scenery::Scene> scene, Parent *parent) :
      scene(scene) {
      flowers::Parent_Implementation::initialize_child(this, parent);
    }

    Scene_Flower::Scene_Flower(Parent *parent) :
      Scene_Flower(
        shared_ptr<scenery::Scene>(new scenery::Scene(lookinglass::House::get_instance().get_viewport_mist())),
        parent) {
      int k = 0;
    }

    void Scene_Flower::render() {
      auto bounds = get_absolute_bounds();
//      auto pos = bounds.get_position();
//      auto position = converter.convert_to_pixels(
//        vec2(pos.x, converter.get_unit_dimensions().y - bounds.get_corner().y));
//      auto dimensions = converter.convert_to_pixels(bounds.get_dimensions());

      auto &converter = Garden::get_instance().get_converter();
      auto pos = bounds.position;
      pos.y = converter.get_pixel_dimensions().y - pos.y - bounds.dimensions.y;
      scene->get_viewport().set_bounds(ivec2(pos) + Viewport::get_active_viewport()->get_position(), bounds.dimensions);

      auto &garden = Garden::get_instance();
      garden.get_draw().enable_3d(true);
      scene->render();
      garden.get_draw().enable_3d(false);
    }
  }

  void flowers::Scene_Flower::set_camera_angle(float degrees) {
    scene->get_camera().set_angle(degrees);
  }

  flowers::Scene_Flower::~Scene_Flower() {

  }
}