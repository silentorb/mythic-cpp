#include "Scene.h"
#include "perspective/Viewport.h"
#include "lookinglass/House.h"

namespace scenery {

  Scene::Scene(lookinglass::House &house) :
    camera(new Camera()),
    house(house),
    root(new Group(nullptr)) {
    viewport = unique_ptr<Viewport>(new Viewport(house.get_viewport_mist(),0,0));
    viewport->set_camera(camera.get());
  }

  Scene::~Scene() { }

  void Scene::render() {
    viewport->activate();
    root->render();
    house.get_base_viewport().activate();
  }
}
