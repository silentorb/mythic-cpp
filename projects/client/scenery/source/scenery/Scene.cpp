#include "Scene.h"
#include "perspective/Viewport.h"
#include "lookinglass/House.h"

namespace scenery {

  Scene::Scene(House &house) :
    camera(new Camera()),
    house(house),
    root(new Group(nullptr)) {
    viewport = unique_ptr<Viewport>(new Viewport(house.get_viewport_mist(),0,0));
    viewport->set_camera(*camera);
  }

  void Scene::render() {
    viewport->activate();
    root->render();
    house.get_base_viewport().activate();
  }
}
