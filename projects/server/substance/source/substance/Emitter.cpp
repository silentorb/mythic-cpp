#include "Emitter.h"
#include <randomly/Dice.h>

namespace substance {

  Emitter::Emitter(const Particle_Generator &generator, Particle_Listener *listener) :
    generator(generator), particle_listener(listener) { }

  Emitter::~Emitter() { }

  void Emitter::update(float delta) {
    for (int i = particles.size() - 1; i >= 0; --i) {
      auto &particle = particles[i];
      particle->update(delta);
      if (particle->is_finished()) {
        if (particle_listener)
          particle_listener->particle_removed(*particle);

        particles.erase(particles.begin() + i);
      }
    }

    const float step = 1 / rate;
    accumulator += delta;
    if (accumulator >= step) {
      int quantity = accumulator / step;
      accumulator -= quantity * step;
      for (int i = 0; i < quantity; ++i) {
        auto particle = generator(delta);
        particle->modify_position(position);
        particles.push_back(unique_ptr<Particle>(particle));
        if (particle_listener)
          particle_listener->particle_added(*particle);
      }
    }
  }

}