#include "Particle.h"

namespace substance {

  void Particle::update(float delta) {
    timer += delta;
    position += velocity * delta;
  }
}