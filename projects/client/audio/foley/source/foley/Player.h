#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <aura/performing/Sound.h>
#include <aura/engineering/Sample_Worker_Mono.h>

namespace aura {
  namespace engineering {
    class Engineer;

    template<typename T>
    class Sample_Worker_Mono;
  }
}

using aura::performing::Sound;

namespace foley {

  template<typename Signal_Type>
  class Player {
      std::vector<std::unique_ptr<Sound<Signal_Type>>> sounds;
      std::vector<std::unique_ptr<Sound<Signal_Type>>> sound_buffer; // For concurrent adding of sounds during playback
      aura::engineering::Engineer &engineer;
      std::unique_ptr<aura::engineering::Sample_Worker_Mono<Player>> sample_worker;

      std::mutex buffer_mutex;

      void manage_sounds() {
        {
          lock_guard<mutex> buffer_lock(buffer_mutex);
          if (sound_buffer.size() > 0) {
            sounds.insert(sounds.end(), make_move_iterator(sound_buffer.begin()),
                          make_move_iterator(sound_buffer.end()));
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

  public:
      Player(aura::engineering::Engineer &engineer) :
        engineer(engineer), sample_worker(new aura::engineering::Sample_Worker_Mono<Player>(this)) {}

      ~Player() {}

      Signal_Type update_sample(float delta) {
        Signal_Type value = 0;
        for (auto &sound : sounds) {
          value += sound->update(delta);
        }
        return value;
      }

      void update(Signal_Type *buffer, int length) {
        manage_sounds();
        sample_worker->update(buffer, length, engineer);
      }

      void add_sound(std::unique_ptr<Sound<Signal_Type>> &sound) {
        lock_guard<mutex> buffer_lock(buffer_mutex);
        sound_buffer.push_back(std::move(sound));
      }

      int get_sound_count() const {
        return sounds.size() + sound_buffer.size();
      }
  };
}