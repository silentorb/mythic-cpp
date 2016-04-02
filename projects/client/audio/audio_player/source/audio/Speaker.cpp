#include "Speaker.h"
#include "Player.h"

namespace audio {

  void Speaker::update(uint8_t *data, int length) {
    player->speaker_update_buffer(data, length);
  }
}
