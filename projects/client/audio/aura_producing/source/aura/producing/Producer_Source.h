#include "Producer.h"
#include <iostream>

namespace aura {

  using namespace engineering;
  using namespace performing;
  using namespace composing;

  namespace producing {

    template<typename Sound_Type, typename Event_Type>
    Producer<Sound_Type, Event_Type>::Producer(Composer<Sound_Type, Event_Type> &composer, Conductor &conductor, Engineer &engineer) :
      composer(composer), conductor(conductor), engineer(engineer),
      performer(new Musical_Performer<Sound_Type, Event_Type>(engineer)) {
      chord_loop = unique_ptr<Tempo_Loop>(new Tempo_Loop(engineer, 32));
      chord_loop->listen([&](Conductor &conductor, float start, float end) {
        composer.get_current_chord_structure().update(conductor, start, end);
      });

      chord_loop->set_on_loop([this](Conductor &conductor, double start, double end) {
        next_section();
        conductor.set_chord(this->composer.get_current_chord_structure().get_chords()[0]);
      });
    }

    template<typename Sound_Type, typename Event_Type>
    Producer<Sound_Type, Event_Type>::~Producer() {
      std::cout << "Deleting Producer.";
    }

    template<typename Sound_Type, typename Event_Type>
    void Producer<Sound_Type, Event_Type>::next_section() {
      composer.next_chord();
      performer->clear_performances();
      auto clips = composer.select_clips();
      for (auto &clip : clips) {
        performer->add_performance(clip->get_instrument(), clip->get_sequencer());
      }
    }

    template<typename Sound_Type, typename Event_Type>
    void Producer<Sound_Type, Event_Type>::commence() {
      next_section();
//      conductor.commence();
    }

    template<typename Sound_Type, typename Event_Type>
    float Producer<Sound_Type, Event_Type>::update(float delta) {
      if (!chord_loop.get())
        return 0;

      chord_loop->update(conductor);
      auto value = performer->update(delta, conductor);
      return value;
    }
  }
}