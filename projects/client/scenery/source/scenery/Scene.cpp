#include <scenery/elements/Model.h>
#include "Scene.h"

namespace scenery {

  void Scene::render(Glass &glass) {
    for (auto element: elements) {
      element->render(glass);
    }
  }

  void Scene::add(elements::Element *element) {
    elements.push_back(element);
  }
}
