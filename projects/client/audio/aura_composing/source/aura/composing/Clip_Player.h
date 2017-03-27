#pragma once

#include <aura/performing/Tempo_Loop.h>
#include "Clip_Composer.h"

namespace aura {
  namespace composing {

    template<typename Sound, typename Event>
    class Clip_Player {
        Clip_Composer<Sound, Event> &composer;
        std::unique_ptr<performing::Tempo_Loop> chord_loop;

            void next_section() {
//      performer->clear_performances();
      composer.next_chord();
//      auto clips = composer.select_clips();
//      for (auto &clip : clips) {
//        performer->add_performance(clip->get_instrument(), clip->get_sequencer());
//      }
    }

    public:
        Clip_Player(Clip_Composer<Sound, Event> &composer, unsigned int sample_rate) : composer(composer) {
          chord_loop = unique_ptr<performing::Tempo_Loop>(new performing::Tempo_Loop(sample_rate, 32));
//          chord_loop->set_on_loop([&](Conductor &conductor, float start, float end) {
//            composer.get_current_chord_structure().update(conductor, start, end);
//          });

          chord_loop->set_on_loop([this](Conductor &conductor, double start, double end) {
            next_section();
//        conductor.set_chord(this->composer.get_current_chord_structure().get_chords()[0]);
          });
        }

        void update(Conductor &conductor) {
          chord_loop->update(conductor);

        }
    };
  }
}