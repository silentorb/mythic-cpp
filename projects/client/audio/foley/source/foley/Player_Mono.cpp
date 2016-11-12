#include "Player_Mono.h"
#include <aura/engineering/Sample_Worker_Mono.h>

using namespace aura::engineering;
using namespace std;

namespace foley {

  Player_Mono::Player_Mono(aura::engineering::Engineer &engineer) :
    engineer(engineer), sample_worker(new Sample_Worker_Mono<Player_Mono, Player_Mono>(this)) {}

  Player_Mono::~Player_Mono() {

  }

  float Player_Mono::update_sample(Player_Mono &self, float delta) {
    float value = 0;
    for (auto &sound : self.sounds) {
      value += sound->update_mono(delta);
    }
    return value;
  }

  void Player_Mono::manage_sounds() {
    {
      lock_guard<mutex> buffer_lock(buffer_mutex);
      if (sound_buffer.size() > 0) {
        sounds.insert(sounds.end(), make_move_iterator(sound_buffer.begin()), make_move_iterator(sound_buffer.end()));
        sound_buffer.clear();
      }
    }

    // This could be performed during the mixing loop but it is a more flexible separation of operations
    // to perform sound removal separately.
    for (int i = sounds.size() - 1; i >= 0; --i) {
      if (sounds[i]->is_finished()) {
        sounds.erase(sounds.begin() + i);
      }
    }
  }

  void Player_Mono::update(float *buffer, int length) {
    manage_sounds();
    sample_worker->update(buffer, length, engineer);
  }

  void Player_Mono::add_sound(unique_ptr<Sound_Performance> &sound) {
    lock_guard<mutex> buffer_lock(buffer_mutex);
    sound_buffer.push_back(std::move(sound));
  }
}