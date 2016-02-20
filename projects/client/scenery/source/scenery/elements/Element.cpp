#include <glm/gtx/transform.hpp>
#include "Element.h"
#include "Group.h"

namespace scenery {
  void Element::render(Glass &glass) {

  }

  mat4 Element::get_transform() const {
    auto transform = glm::translate(position)
           * glm::scale(scale)
           * glm::mat4_cast(orientation);

    if (parent)
      transform = transform * parent->get_transform();

    return transform;
  }
}
