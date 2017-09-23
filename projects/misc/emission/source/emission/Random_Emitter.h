#pragma once

#include "Emitter_Base.h"

namespace randomly {
  class Dice;
}

namespace emission {

  template<typename Particle_Type>
  class Random_Emitter : public Emitter_Base<Particle_Type> {
  protected:
      randomly::Dice &dice;
      virtual void generate(float delta);

  public:
      Random_Emitter(const Empty_Delegate &factory, randomly::Dice &dice) :
        Emitter_Base<Particle_Type>(factory), dice(dice) {

      }
  };
}