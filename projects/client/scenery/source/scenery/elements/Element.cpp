#include <glm/gtx/transform.hpp>
#include "Element.h"
#include "Group.h"

namespace scenery {

  void Element::render() {

  }

  mat4 Element::get_transform() {
    auto transform = glm::translate(position)
                     * glm::scale(scale)
                     * glm::mat4_cast(orientation);

    if (parent && parent->has_transform())
      transform = parent->get_transform() * transform;

    return transform;
  }

  mat4 Element::get_absolute_orientation() {
    auto transform = glm::mat4_cast(orientation);

    if (parent && parent->has_transform())
      transform = parent->get_absolute_orientation() * transform;

    return transform;
  }

  void Element::update(float delta) { }

  void Element::get_absolute_position_and_orientation(vec3 &out_position, quat &out_orientation) {
    auto transform = get_transform();
    out_position = vec3(transform[3]);
    out_orientation = quat(transform);
  }

  void Element::move_to_absolute() {
    get_absolute_position_and_orientation(position, orientation);
  }

  void Element::set_parent(Parent *new_parent, bool update_others) {
    if (parent == new_parent)
      return;

    if (!update_others) {
      parent = new_parent;
      return;
    }

    if (parent && new_parent) {
      this->parent->move_child(*this, *new_parent);
    }
    else if (new_parent) {
      parent->add_child(*this);
    }
    else {
      remove();
    }
  }
}
