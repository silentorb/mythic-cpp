#include "Group.h"

namespace scenery {

  void Group::render(lookinglass::Glass &glass) {
    for (auto &element: elements) {
      element->render(glass);
    }
  }

  void Group::add(unique_ptr<Element> element) {
    element->set_parent(this);
    elements.push_back(std::move(element));
  }
}