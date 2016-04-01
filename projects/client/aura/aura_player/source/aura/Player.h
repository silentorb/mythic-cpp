#pragma once

#include "dllexport.h"
#include "Sound.h"
#include <vector>

using namespace std;

namespace aura {

  class Speaker;

  class MYTHIC_EXPORT Player {
      friend class Speaker;

      vector<Sound> sounds;
      unique_ptr<Speaker> speaker;
      float last_delta;

      void speaker_update_buffer(uint8_t *data, int length);

  public:

      Player(Speaker*speaker);
      ~Player();
      void play(Waveform &waveform);
      void update(float delta);
  };
}