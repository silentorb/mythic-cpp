#include "Tempo_Loop.h"
#include "aura/sequencing/Conductor.h"

namespace aura {

  void Tempo_Loop::update(Conductor &conductor) {
    loop.set_frequency(conductor.get_tempo() / 60 / beats);
    auto old = loop.get_position();
    auto next = loop.next();
    for(auto &handler: handlers){
      handler(conductor, old, next);
    }
  }
}