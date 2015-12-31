#pragma once
#include "dllexport.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"

using namespace glm;

namespace lookinglass {
  namespace perspective {

    class MYTHIC_EXPORT Camera {
    private:
        vec3 position;
        quat orientation;

    public:
        mat4 get_view_matrix();

        const vec3 &get_position() const {
          return position;
        }

        void set_position(const vec3 &position) {
          Camera::position = position;
        }

        const quat &get_orientation() const {
          return orientation;
        }

        void set_orientation(const quat &orientation) {
          Camera::orientation = orientation;
        }
    };

  }
}