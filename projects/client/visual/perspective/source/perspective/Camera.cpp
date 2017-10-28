#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include "logger.h"

namespace perspective {

  const mat4 Camera::get_view_matrix() const {
    auto forward = orientation * vec3(1, 0, 0);
    auto look_at = position + forward;
    return glm::lookAt(position, look_at, vec3(0, 0, 1));
  }
}
