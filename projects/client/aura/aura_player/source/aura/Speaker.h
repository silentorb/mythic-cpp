#pragma once

#include "dllexport.h"
#include <cstdint>

namespace aura {

  class Player;

  class MYTHIC_EXPORT Speaker {
      Player *player;

  public:
      virtual void start() = 0;
      virtual void stop() = 0;
      void update(uint8_t *data, int length);

      void set_player(Player *player) {
        this->player = player;
      }
  };
}