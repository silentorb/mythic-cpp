#pragma once

#include "Sound.h"
#include <vector>
#include <memory>
#include <mutex>

namespace aura {
  namespace engineering {
    class Engineer;

    template<typename T, typename Static_Class>
    class Sample_Worker_Mono;
  }
}

namespace foley {

  class Player_Mono {
      std::vector<std::unique_ptr<Sound>> sounds;
      std::vector<std::unique_ptr<Sound>> sound_buffer; // For concurrent adding of sounds during playback
      aura::engineering::Engineer &engineer;
      std::unique_ptr<aura::engineering::Sample_Worker_Mono<Player_Mono, Player_Mono>> sample_worker;

      std::mutex buffer_mutex;

  public:
      Player_Mono(aura::engineering::Engineer &engineer);
      ~Player_Mono();
      static float update_sample(Player_Mono &self, float delta);
      void update(float *buffer, int length);
      void add_sound(std::unique_ptr<Sound> &sound);
  };
}