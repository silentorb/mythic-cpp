#pragma once

#include "Random_Emitter.h"
#include "Emitter_Base_Source.h"
#include <randomly/Dice.h>

namespace emission {

  template<typename Particle_Type>
  void Random_Emitter<Particle_Type>::generate(float delta) {
    if (delta > 0.1) {
      delta = 0.1;
    }
    auto likelihood = this->rate * delta;
    if (dice.get_float() <= likelihood) {
      this->particles.push_back(std::unique_ptr<Particle_Type>(this->factory()));
    }
  };
}