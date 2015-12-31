#include "Camera.h"
#include <glm/gtx/transform.hpp>

namespace lookinglass {
  namespace perspective {




    mat4 Camera::get_view_matrix() {
      auto translation = glm::translate(position);
      auto rotation = glm::mat4_cast(orientation);
      return translation * rotation;
    }
  }
}