#include "Scene.h"
#include "perspective/Viewport.h"

using namespace perspective;

namespace scenery {

  Scene::Scene(through::Mist<Viewport_Data> &viewport_mist) :
    camera(new Camera()),
    root(new Group()) {
    viewport = unique_ptr<Viewport>(new Viewport(viewport_mist, 0, 0));
    viewport->set_camera(camera.get());
  }

  Scene::~Scene() {}

  void Scene::render() {
    auto previous_viewport = Viewport::get_active_viewport();
    viewport->activate();
    root->render();
    previous_viewport->activate();
  }
}
