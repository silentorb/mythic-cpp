#pragma once

#include "dllexport.h"
#include "glm/vec4.hpp"
#include <substance/Particle.h>

using namespace glm;

namespace scenery {

  class MYTHIC_EXPORT Pretty_Particle : public substance::Particle {
      float size;
      vec4 color;

  public:

      Pretty_Particle(const vec3 &position, float size, const vec4 &color) : color(color), size(size) {
        substance::Particle::set_position(position);
      }

      const vec4 &get_color() const {
        return color;
      }

      void set_color(const vec4 &color) {
        Pretty_Particle::color = color;
      }

      float get_size() const {
        return size;
      }

      void set_size(float size) {
        Pretty_Particle::size = size;
      }
  };
}