#include "Producer.h"
#include "Performer.h"

namespace aura {

  Producer::Producer(Composer &composer, Conductor &conductor, Engineer &engineer) :
    composer(composer), conductor(conductor) {
    chord_loop = unique_ptr<Tempo_Loop>(new Tempo_Loop(engineer, 32));
    chord_loop->set_position(0.99);
    chord_loop->listen([&](Conductor &conductor, float start, float end) {
      perform_chord_structure(conductor, composer.get_current_chord_structure(), start, end);
    });
  }

  void Producer::update() {
    chord_loop->update(conductor);
  }
}