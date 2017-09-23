#include <cmath>
#include <math/utility.h>
#include <memory.h>
#include "Player.h"
#include "Speaker.h"

using namespace std;

namespace audio {

  Player::Player(Speaker *speaker) : speaker(speaker) {
    speaker->set_player(this);
    device_settings = speaker->start();
  }

  Player::~Player() {
    unique_lock<mutex>(m);
    speaker->stop();
    source.reset();
  }

//  void Player::play(Waveform &waveform) {
//    sounds.push_back({waveform, 0});
//  }

  void Player::speaker_update_buffer(float *data, int data_length) {
    unique_lock<mutex>(m);
    if (auto pointer = source.lock()) {
      pointer->update_buffer(data, data_length);
    }

  }
}
