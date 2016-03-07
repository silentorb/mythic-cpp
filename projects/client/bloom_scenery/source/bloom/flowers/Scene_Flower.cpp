#include "Scene_Flower.h"
#include "scenery/Scene.h"

namespace bloom {

  Scene_Flower::Scene_Flower(Garden &garden, shared_ptr<scenery::Scene> &scene, Flower *parent) :
    scene(scene),
    Flower(garden, parent) {

  }

  void Scene_Flower::render() {
    scene->render();
    Flower::render();
  }
}
