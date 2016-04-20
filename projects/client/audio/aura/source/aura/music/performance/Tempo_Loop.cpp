#include "Tempo_Loop.h"
#include "aura/sequencing/Conductor.h"

namespace aura {

  void Tempo_Loop::update(Conductor &conductor) {
    loop.set_frequency(conductor.get_tempo() / 60 / beats);
    auto old = loop.get_position();
    bool looped;
    auto next = loop.next(looped);
    if (looped && on_loop) {
      on_loop(conductor, old, next);
    }

    trigger(conductor, old, next);
  }

}