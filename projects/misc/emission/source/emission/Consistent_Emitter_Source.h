#pragma once
#include "Consistent_Emitter.h"
#include "Emitter_Base_Source.h"

namespace emission {

  template<typename Particle_Type>
  void Consistent_Emitter<Particle_Type>::generate(float delta) {
    if (delta > 0.1) {
      delta = 0.1;
    }
    const float step = 1 / this->rate;
    accumulator += delta;
    while (accumulator >= step) {
      accumulator -= step;
      this->particles.push_back(std::unique_ptr<Particle_Type>(this->factory()));
    }
  };
}