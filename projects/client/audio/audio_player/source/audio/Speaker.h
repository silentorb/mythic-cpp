#pragma once

#include "dllexport.h"
#include "Device_Settings.h"
#include <cstdint>

namespace audio {

  class Player;

  class MYTHIC_EXPORT Speaker {
      Player *player;

  public:
      virtual Device_Settings start() = 0;
      virtual void stop() = 0;

      void update(uint8_t *data, int length);

      void set_player(Player *player) {
        this->player = player;
      }
  };
}