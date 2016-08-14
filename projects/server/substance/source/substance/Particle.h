#pragma once

#include "commoner/dllexport.h"
#include <glm/vec3.hpp>

using namespace glm;

namespace substance {

  class MYTHIC_EXPORT Particle {
      vec3 position;
      vec3 velocity;
      vec3 acceleration;
      float lifetime = 1;
      float timer = 0;

  public:

      Particle() { }

      Particle(const vec3 &position) : position(position) { }

      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        Particle::position = position;
      }

      void modify_position(const vec3 offset) {
        position += offset;
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

      bool is_finished() const {
        return timer >= lifetime;
      }

      void update(float delta);

      float get_life() const {
        return timer / lifetime;
      }
  };
}