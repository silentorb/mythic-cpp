#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include "logger.h"

namespace perspective {

  mat4 Camera::get_view_matrix() {
    auto forward = orientation * vec3(0, 1, 0);
    auto look_at = position + forward;
    return glm::lookAt(position, look_at, vec3(0, 0, 1));
  }
}
