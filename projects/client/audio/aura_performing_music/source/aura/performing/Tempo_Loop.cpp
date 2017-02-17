#include "Tempo_Loop.h"
#include "aura/sequencing/Conductor.h"

using namespace aura::sequencing;

namespace aura {
  namespace performing {

    void Tempo_Loop::update(Conductor &conductor) {
      auto frequency = conductor.get_tempo() / 60 / beats;
      loop.set_frequency(frequency);
      bool looped;
      loop.update(looped);
      auto next = loop.get_next();
      if (looped && on_loop) {
        on_loop(conductor, last_time, next);
      }
    }
  }
}