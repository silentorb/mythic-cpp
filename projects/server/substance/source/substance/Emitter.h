#pragma once

#include "dllexport.h"
#include "Particle.h"
#include <vector>
#include <memory>

using namespace std;

namespace substance {

  class MYTHIC_EXPORT Emitter {
      vector<Particle> particles;
      shared_ptr<randomly::Dice> dice;

  public:

      void update(float delta);
  };
}