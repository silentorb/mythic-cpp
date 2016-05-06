#include "Tempo_Loop.h"
#include "aura/sequencing/Conductor.h"

namespace aura {

  void Tempo_Loop::update(Conductor &conductor) {
    auto frequency = conductor.get_tempo() / 60 / beats;
    loop.set_frequency(frequency);
//    auto old = loop.get_position();
    bool looped;
    auto next = loop.next(looped);
    if (looped && on_loop) {
      on_loop(conductor, last_time, next);
    }

    if (skip++ == 100 || !started) {
      trigger(conductor, last_time, next);
      skip = 0;
      last_time = next;
      started = true;
    }
  }

}