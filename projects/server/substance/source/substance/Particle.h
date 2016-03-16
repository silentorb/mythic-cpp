#pragma once

#include "dllexport.h"
#include <glm/vec3.hpp>

using namespace glm;

namespace substance {

  class MYTHIC_EXPORT Particle {
      vec3 position;
      vec3 velocity;
      vec3 acceleration;

  public:

      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        Particle::position = position;
      }

      const vec3 &get_velocity() const {
        return velocity;
      }

      void set_velocity(const vec3 &velocity) {
        Particle::velocity = velocity;
      }

      const vec3 &get_acceleration() const {
        return acceleration;
      }

      void set_acceleration(const vec3 &acceleration) {
        Particle::acceleration = acceleration;
      }
  };
}