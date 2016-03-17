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
}
