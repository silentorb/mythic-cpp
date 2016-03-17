#pragma once

#include "dllexport.h"
#include "Particle.h"
#include <vector>
#include <memory>
#include <functional>

namespace randomly {
  class Dice;
}
using namespace std;

namespace substance {

  typedef function<Particle*(float)> Particle_Generator;

  class MYTHIC_EXPORT Particle_Listener {
  public:
      virtual void particle_added(Particle &particle) = 0;
      virtual void particle_removed(Particle &particle) = 0;
  };

  class MYTHIC_EXPORT Emitter: no_copy {
      vector<unique_ptr<Particle>> particles;
      Particle_Generator generator;
      float rate = 1; // per second
      vec3 position;
      Particle_Listener* particle_listener = nullptr;

      float accumulator = 0;

  public:

      Emitter(const Particle_Generator &generator, Particle_Listener* listener);
      ~Emitter();

      void update(float delta);

      const vec3 &get_position() const {
        return position;
      }

      void set_position(const vec3 &position) {
        Emitter::position = position;
      }

      void set_rate(float rate) {
        Emitter::rate = rate;
      }
  };
}