#pragma once

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"

using namespace glm;

namespace lookinglass {
  namespace perspective {

    class Camera {
    private:
        vec3 position;
        quat orientation;

    public:
        mat4 get_view_matrix();
        vec3 get_position();
        quat get_orientation();
    };

  }
}