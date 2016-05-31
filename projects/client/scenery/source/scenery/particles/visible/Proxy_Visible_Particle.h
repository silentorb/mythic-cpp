#pragma once

#include "Visible_Particle.h"

using namespace glm;

namespace scenery {

  class MYTHIC_EXPORT Proxy_Visible_Particle : public Visible_Particle {
      const substance::Particle &seed;

  public:
      Proxy_Visible_Particle(const substance::Particle &seed) :
        seed(seed) {

      }

      Proxy_Visible_Particle(const substance::Particle &seed, float size, const vec4 &color) :
        seed(seed), Visible_Particle(size, color) {

      }

      virtual const vec3 get_position() const override {
        return seed.get_position();
      }

      virtual const Particle *get_particle() const override {
        return &seed;
      }

  };
}