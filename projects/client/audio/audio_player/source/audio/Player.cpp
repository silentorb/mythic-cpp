#include <cmath>
#include <math/utility.h>
#include <memory.h>
#include "Player.h"
#include "Speaker.h"

namespace audio {

  Player::Player(Speaker *speaker) : speaker(speaker) {
    source = [](unsigned char *data, int length) {
      memset(data, 0, length);
    };
    speaker->set_player(this);
    device_settings = speaker->start();
  }

  Player::~Player() {
    speaker->stop();
  }

  void Player::play(Waveform &waveform) {
    sounds.push_back({waveform, 0});
  }

//  void Player::update(float delta) {
//    last_delta = delta;
//  }

  void Player::speaker_update_buffer(uint8_t *data, int data_length) {
    source(data, data_length);

//    float *buffer = (float *) data;
//    int length = (data_length / sizeof(float));
//    for (int i = 0; i < length; ++i) {
//      buffer[i] = (float) sin(current * 2 * Pi);
//      if (device_settings.channel_count == 2)
//        buffer[++i] = (float) sin(current);
//
////      current += 0.05f;
//      current = fmod(current + 1000.0f / device_settings.sample_rate, 1.0);
//    }

  }
}