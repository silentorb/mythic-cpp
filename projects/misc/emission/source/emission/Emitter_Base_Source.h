#pragma once

#include "Emitter_Base.h"

namespace emission {

  template<typename Particle_Type>
  void Emitter_Base<Particle_Type>::update_particles(float delta) {
//    for (int i = particles.size() - 1; i >= 0; --i) {
//      auto &particle = particles[i];
    if (particles.size() == 0)
      return;

    auto particle = particles.data() + particles.size();
    while (particle != particles.data())
      --particle;
    if (updater)
      updater(*particle->get(), delta);

    if (particle->get()->is_finished()) {
      if (on_delete)
        on_delete(*particle->get());

      particles.erase(particles.begin() + (particle - particles.data()));
    }
  };

  template<typename Particle_Type>
  void Emitter_Base<Particle_Type>::operator()(float delta) {
    update_particles(delta);
    generate(delta);
  }


}