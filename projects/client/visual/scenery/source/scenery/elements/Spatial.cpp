#include "Spatial.h"
#include <glm/gtx/transform.hpp>

namespace scenery {

  Spatial::Spatial() :
    position(vec3(0)), orientation(quat()), scale(vec3(1)), Simple_Element() {}

  mat4 &Spatial::get_absolute_orientation() {
    orientation_transform = glm::mat4_cast(orientation);

    if (parent)
      orientation_transform = parent->get_spatial().get_absolute_orientation() * orientation_transform;

    return orientation_transform;
  }

  mat4 &Spatial::get_transform() {
    transform =
      glm::translate(position)
      * glm::scale(scale)
      * glm::mat4_cast(orientation);

    if (parent)
      transform = parent->get_spatial().get_transform() * transform;

    return transform;
  }
}