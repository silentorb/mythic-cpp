#include "Particle.h"

namespace substance {

  void Particle::simple_update(Particle &particle, float delta) {
    particle.modify_timer(delta);
    particle.modify_position(particle.get_velocity() * delta);
  }
}