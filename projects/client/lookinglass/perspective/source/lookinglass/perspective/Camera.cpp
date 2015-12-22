#include "Camera.h"
#include <glm/gtx/transform.hpp>

namespace lookinglass {
  namespace perspective {


    vec3 Camera::get_position() {
      return position;
    }

    quat Camera::get_orientation() {
      return orientation;
    }

    mat4 Camera::get_view_matrix() {
      auto translation = glm::translate(position);
      auto rotation = glm::mat4_cast(orientation);
      return translation * rotation;
    }
  }
}