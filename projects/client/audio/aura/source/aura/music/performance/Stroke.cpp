#include "Stroke.h"
#include "aura/sequencing/Note.h"
#include "aura/sequencing/Conductor.h"

namespace aura {

  Stroke::Stroke(const Note &note) :
    duration(note.get_duration()),
    frequency(note.get_frequency()),
    note(note) { }

  float Stroke::update(float delta, Conductor &conductor) {
    auto k = conductor.get_seconds_tempo() * delta;
    progress += k;
//    progress += delta;
    return 0;
  }
}