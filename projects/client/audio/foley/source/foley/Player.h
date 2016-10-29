#pragma once

#include "Sound.h"
#include <vector>
#include <memory>

namespace aura {
  namespace engineering {
    class Engineer;
    template<typename T, typename Static_Class>
    class Sample_Worker;
  }
}

namespace foley {

  class Player {
      std::vector<std::unique_ptr<Sound>> sounds;
      std::vector<std::unique_ptr<Sound>> buffer;
      aura::engineering::Engineer &engineer;
      std::unique_ptr<aura::engineering::Sample_Worker<Player, Player>> sample_worker;

  public:
      Player(aura::engineering::Engineer &engineer);
      ~Player();
      static void update_sample(Player & self,float *buffer, float delta);
      void update(float *buffer, int length);
//      void add_sound(Sound *sound);
      void add_sound(std::unique_ptr<Sound> sound);
  };
}