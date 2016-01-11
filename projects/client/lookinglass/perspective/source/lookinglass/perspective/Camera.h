#pragma once

#include "dllexport.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"
#include "spatial/Positioned_Oriented.h"

using namespace glm;
using namespace spatial;

namespace lookinglass {
  namespace perspective {

    class MYTHIC_EXPORT Camera : public Positioned_Oriented {
    private:
        vec3 position;
        quat orientation;

    public:
        mat4 get_view_matrix();

        const vec3 &get_position() const override {
          return position;
        }

        void set_position(const vec3 &position) override {
          Camera::position = position;
        }

        const quat &get_orientation() const override {
          return orientation;
        }

        void set_orientation(const quat &orientation) override {
          Camera::orientation = orientation;
        }
    };

  }
}