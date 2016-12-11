#pragma once

#include "Emitter_Base.h"

namespace emission {

  template<typename Particle_Type>
  class Consistent_Emitter : public Emitter_Base<Particle_Type> {
  protected:
      float accumulator = 0;
      virtual void generate(float delta);

  public:
      Consistent_Emitter(const Particle_Factory<Particle_Type> &factory) :
        Emitter_Base<Particle_Type>(factory) {

      }
  };
}