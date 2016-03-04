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
    if (element->get_parent() && element->get_parent() != this) {
      element->get_parent()->move_child(element, *this);
    }
    else {
      element->set_parent(this, false);
      elements.push_back(std::move(element));
    }
  }

  void Group::add_child(Element& element) {
    if (element.get_parent() && element.get_parent() != this) {
      element.get_parent()->move_child(element, *this);
    }
    else {
      element.set_parent(this, false);
      elements.push_back(unique_ptr<Element>(&element));
    }
  }

  bool Group::has_transform() {
    return true;
  }

  mat4 Group::get_transform() {
    return Element::get_transform();
  }

  void Group::move_child(unique_ptr<Element> &element, Parent &destination) {
    int offset = std::find_if(elements.begin(), elements.end(), [&](unique_ptr<Element> const &item) {
      return item.get() == element.get();
    }) - elements.begin();

    element->set_parent(nullptr);
    destination.add_child(std::move(elements[offset]));
    elements.erase(elements.begin() + offset);
  }

  void Group::move_child(Element &element, Parent &destination) {
    int offset = std::find_if(elements.begin(), elements.end(), [&](unique_ptr<Element> const &item) {
      return item.get() == &element;
    }) - elements.begin();

    element.set_parent(nullptr);
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