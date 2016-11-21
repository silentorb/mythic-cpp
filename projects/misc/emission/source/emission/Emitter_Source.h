#pragma once

#include "Emitter.h"

namespace emission {

  template<typename Particle_Type>
  void Emitter<Particle_Type>::update_particles(float delta) {
    for (int i = particles.size() - 1; i >= 0; --i) {
      auto &particle = particles[i];
      if (updater)
        updater(*particle, delta);

      if (particle->is_finished()) {
        if (on_delete)
          on_delete(*particle);

        particles.erase(particles.begin() + i);
      }
    }
  };

  template<typename Particle_Type>
  void Emitter<Particle_Type>::generate(float delta) {
    if (delta > 0.1) {
      delta = 0.1;
    }
    const float step = 1 / rate;
    accumulator += delta;
    while (accumulator >= step) {
      accumulator -= step;
      particles.push_back(std::unique_ptr<Particle_Type>(factory()));
    }
  };

  template<typename Particle_Type>
  void Emitter<Particle_Type>::operator()(float delta) {
    update_particles(delta);
    generate(delta);
  }


}