#include "Group.h"
#include <algorithm>

namespace scenery {

  void Group::render(lookinglass::Glass &glass) {
    for (auto &element: elements) {
      if (element->is_visible())
        element->render(glass);
    }
  }

  void Group::add_child(unique_ptr<Element> element) {
    element->set_parent(this);
    elements.push_back(std::move(element));
  }

  bool Group::has_transform() {
    return true;
  }

  mat4 Group::get_transform() {
    return Element::get_transform();
  }

  void Group::move_child(unique_ptr<Element> &element, Parent &destination) {
//    destination.add(std::move(element));
//    auto offset = std::find(elements.begin(), elements.end(), [=](std::unique_ptr<int> &p) {
//      return p.get() == nullptr;
//    }) - elements.begin();
//    elements.erase(elements.begin() + offset);
  }

  void Group::move_child(Element &element, Parent &destination) {
    int offset = std::find_if(elements.begin(), elements.end(), [&](unique_ptr<Element> const &item) {
      return item.get() == &element;
    }) - elements.begin();

    destination.add_child(std::move(elements[offset]));
    elements.erase(elements.begin() + offset);
  }

  void Group::remove_child(Element &element) {
    int offset = std::find_if(elements.begin(), elements.end(), [&](unique_ptr<Element> const &item) {
      return item.get() == &element;
    }) - elements.begin();

    elements.erase(elements.begin() + offset);
  }
}