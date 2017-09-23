#pragma once

#include "Random_Emitter.h"
#include "Emitter_Base_Source.h"
#include <randomly/Dice.h>

namespace emission {

  template<typename Particle_Type>
  void Random_Emitter<Particle_Type>::generate(float delta) {
    if (this->rate == 0)
      return;

    if (delta > 0.1) {
      delta = 0.1;
    }
    auto likelihood = this->rate * delta;
    if (dice.get_float() <= likelihood) {
      this->factory();
//      auto particle = std::unique_ptr<Particle_Type>(this->factory());
//      this->particles.push_back(particle);
    }
  };
}