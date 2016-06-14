#include <cmath>
#include <math/utility.h>
#include <memory.h>
#include "Player.h"
#include "Speaker.h"

namespace audio {

  Player::Player(Speaker *speaker) : speaker(speaker) {
    source = [](float *data, int length) {
      memset(data, 0, length);
    };
    speaker->set_player(this);
    device_settings = speaker->start();
  }

  Player::~Player() {
		unique_lock<mutex>(m);
		speaker->stop();
  }

  void Player::play(Waveform &waveform) {
    sounds.push_back({waveform, 0});
  }

  void Player::speaker_update_buffer(float *data, int data_length) {
		unique_lock<mutex>(m);
		source(data, data_length);

  }
}
