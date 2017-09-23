#pragma once

#include "Emitter_Base.h"

namespace emission {

  template<typename Particle_Type>
  void Emitter_Base<Particle_Type>::operator()(float delta) {
//    update_particles(delta);
    generate(delta);
  }


}