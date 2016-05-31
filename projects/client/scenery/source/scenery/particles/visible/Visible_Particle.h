#pragma once

#include "dllexport.h"
#include "glm/vec4.hpp"
#include "scenery/particles/Point_Emitter_Bridge.h"
#include <substance/Particle.h>

using namespace glm;

namespace scenery {

  class MYTHIC_EXPORT Visible_Particle {
      float size = 1;
      vec4 color = vec4(1, 1, 1, 1);
      Particle_Point_Delegate *animator = nullptr;

  protected:
      Visible_Particle() :
        color(vec4(1, 1, 1, 1)), size(1) { }

      Visible_Particle(float size, const vec4 &color) :
        color(color), size(size) { }

  public:

      const vec4 &get_color() const {
        return color;
      }

      void set_color(const vec4 &color) {
        Visible_Particle::color = color;
      }

      float get_size() const {
        return size;
      }

      void set_size(float size) {
        Visible_Particle::size = size;
      }

      virtual const vec3 get_position() const = 0;

      void update(float delta) {
        if (animator) {
          (*animator)(*this);
        }
      }

      virtual const Particle *get_particle() const = 0;
  };
}