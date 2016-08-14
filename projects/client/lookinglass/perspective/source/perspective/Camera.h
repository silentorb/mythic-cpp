#pragma once

#include "commoner/dllexport.h"

#include "glm/gtc/quaternion.hpp"
#include "glm/vec3.hpp"
#include "spatial/Positioned_Oriented.h"

using namespace glm;
using namespace spatial;

namespace perspective {

  class MYTHIC_EXPORT Camera : public Positioned_Oriented {
  private:
      vec3 position;
      quat orientation;
      float angle = glm::radians(45.0f);

  public:

      Camera() {}

      Camera(const vec3 &position, const quat &orientation, float angle) : position(position), orientation(orientation),
                                                                           angle(angle) {}

      virtual ~Camera() {}

      virtual mat4 get_view_matrix();

      vec3 &get_position() override {
        return position;
      }

      void set_position(const vec3 &position) override {
        Camera::position = position;
      }

      quat &get_orientation() override {
        return orientation;
      }

      void set_orientation(const quat &orientation) override {
        Camera::orientation = orientation;
      }

      void set_all(const vec3 &position, const quat &orientation, float degrees) {
        set_position(position);
        set_orientation(orientation);
        set_degrees(degrees);
      }

      float &get_angle() {
        return angle;
      }

      void set_angle(float angle) {
        this->angle = angle;
      }

      void set_degrees(float angle) {
        this->angle = glm::radians(angle);
      }
  };

}