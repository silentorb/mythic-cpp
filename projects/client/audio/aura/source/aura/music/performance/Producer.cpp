#include "Producer.h"
#include "Performer.h"
#include <iostream>

namespace aura {

  Producer::Producer(Composer &composer, Conductor &conductor, Engineer &engineer) :
    composer(composer), conductor(conductor), engineer(engineer),
    performer(new Performer(engineer)) {
    chord_loop = unique_ptr<Tempo_Loop>(new Tempo_Loop(engineer, 32));
    chord_loop->listen([&](Conductor &conductor, float start, float end) {
      perform_chord_structure(conductor, composer.get_current_chord_structure(), start, end);
    });

    chord_loop->set_on_loop([this](Conductor &conductor, float start, float end) {
      next_section();
      conductor.set_chord(this->composer.get_current_chord_structure().get_chords()[0], 0, start, end);
    });
  }

  Producer::~Producer() {
    std::cout << "Deleting Producer.";
  }

  void Producer::next_section() {
    composer.next_chord();
    performer->clear_performances();
    auto clips = composer.select_clips();
    for (auto &clip : clips) {
      performer->add_performance(clip->get_instrument(), clip->get_sequencer(), clip->get_group_id());
    }
  }

  void Producer::commence() {
    next_section();
    conductor.commence();
  }

  float Producer::update(float delta) {
    if (!chord_loop.get())
      return 0;

    chord_loop->update(conductor);
    auto value = performer->update(delta, conductor);
    return value;
  }


}