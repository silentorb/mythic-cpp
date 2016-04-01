#include <cmath>
#include "Player.h"
#include "Speaker.h"

namespace aura {

  Player::Player(Speaker *speaker) : speaker(speaker) {
    speaker->set_player(this);
    speaker->start();
  }

  Player::~Player() {
    speaker->stop();
  }

  void Player::play(Waveform &waveform) {
    sounds.push_back({waveform, 0});
  }

  void Player::update(float delta) {
    last_delta = delta;
  }

  void Player::speaker_update_buffer(uint8_t *data, int data_length) {
//    for (auto &sound: sounds) {
//      for (int i = 0; i < length; ++i) {
//
//      }
//    }

    float *buffer = (float *) data;
    int length = (data_length / sizeof(float)) / 2;
    float increment = last_delta / length;
    float current = 0;
    for (int i = 0; i < length; ++i) {
      buffer[i] = (float)sin(current);
      buffer[++i] = (float)sin(current);
        current += increment;
    }
  }
}