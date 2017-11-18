#include "Transform.h"
#include <glm/gtx/transform.hpp>

namespace spatial_old {

  const mat4 &Transform::get_matrix() {
    matrix =
      glm::translate(position)
      * glm::scale(scale)
      * glm::mat4_cast(orientation);

    if (parent)
      matrix = parent->get_matrix() * matrix;

    return matrix;
  }
}