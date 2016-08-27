#include "Group.h"
#include <algorithm>

namespace drawing {

  Group::~Group() {
    for (auto element: elements) {
      delete element;
    }
  }

  void Group::render() {
    for (auto &element : elements) {
      element->render();
    }
  }

//  void Group::add(Element &element) {
//    elements.push_back(&element);
//  }

  void Group::remove(Element &element) {
    elements.erase(std::remove(elements.begin(), elements.end(), &element), elements.end());
  }

  void Group::move(Element &element, Group &target) {
    target.elements.push_back(&element);
    elements.erase(std::remove(elements.begin(), elements.end(), &element), elements.end());
  }
}