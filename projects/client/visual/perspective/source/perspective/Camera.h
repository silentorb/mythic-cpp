#pragma once

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"
#include "spatial_old/Positioned_Oriented.h"

using namespace glm;
using namespace spatial_old;

namespace perspective {

  class Camera {
  private:
      vec3 position;
      quat orientation;
      float angle = 45.0f;

  public:

      Camera() {}

      Camera(const vec3 &position, const quat &orientation, float angle) : position(position), orientation(orientation),
                                                                           angle(angle) {}

      const mat4 get_view_matrix() const;

      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        Camera::position = position;
      }

      const quat &get_orientation() const {
        return orientation;
      }

      void set_orientation(const quat &value) {
        orientation = value;
      }

      void set_all(const vec3 &position, const quat &orientation, float degrees) {
        set_position(position);
        set_orientation(orientation);
        set_angle(degrees);
      }

      const float &get_angle() const {
        return angle;
      }

      void set_angle(float angle) {
        this->angle = angle;
      }

//      void set_degrees(float angle) {
//        this->angle = glm::radians(angle);
//      }
  };

}