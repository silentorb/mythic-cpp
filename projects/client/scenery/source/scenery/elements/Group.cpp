#include "Group.h"
#include "Spatial_Source.h"
#include <algorithm>

namespace scenery {

  void Group::render() {
//    if (is_visible()) {
//    auto base_transform = get_transform();
    for (auto &element: children) {
//        if (element->is_visible())
      element->render();
    }
//    }
  }

  void Group::add_child(unique_ptr<Element> element) {
    if (element->get_parent() && element->get_parent() != this) {
      element->get_parent()->move_child(element, *this);
    }
    else {
      element->set_parent(this, false);
      children.push_back(std::move(element));
    }
  }

  void Group::add_child(Element &element) {
    if (element.get_parent() && element.get_parent() != this) {
      element.get_parent()->move_child(element, *this);
    }
    else {
      element.set_parent(this, false);
      children.push_back(unique_ptr<Element>(&element));
    }
  }

//  bool Group::has_transform() {
//    return true;
//  }

  void Group::move_child(Element &element, Parent &destination) {
    for (int i = 0; i < children.size(); ++i) {
      if (children[i].get() == &element) {
        element.set_parent(nullptr, false);
        destination.add_child(std::move(children[i]));
        children.erase(children.begin() + i);
        break;
      }
    }
  }

  void Group::remove_child(Element &element) {
    int offset = std::find_if(children.begin(), children.end(), [&](unique_ptr<Element> const &item) {
      return item.get() == &element;
    }) - children.begin();

    children.erase(children.begin() + offset);
  }

  void Group::clear() {
    children.clear();
  }

  void Group::update(float delta) {
    for (auto &element: children) {
//      if (element->is_visible())
      element->update(delta);
    }
  }

  void Group::move_child(unique_ptr<Element> &element, Parent &destination) {
    move_child(*element, destination);
  }
}