#pragma once

#include "Visible_Particle.h"

using namespace glm;

namespace scenery {

  class MYTHIC_EXPORT Contained_Visible_Particle : public Visible_Particle {
      substance::Particle seed;

  public:
      Contained_Visible_Particle() {

      }

      Contained_Visible_Particle(vec3 position, float size, const vec4 &color) :
        Visible_Particle(size, color) {
        seed.set_position(position);
      }

      virtual const vec3 get_position() const override {
        return seed.get_position();
      }

      virtual const Particle *get_particle() const override {
        return &seed;
      }

  };
}