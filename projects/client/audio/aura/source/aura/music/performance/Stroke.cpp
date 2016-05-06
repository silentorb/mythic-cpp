#include "Stroke.h"
#include "aura/sequencing/Note.h"

namespace aura {

  Stroke::Stroke(const Note &note) :
    duration(note.get_duration()),
    frequency(note.get_frequency()),
    note(note) { }

  float Stroke::update(float delta) {
    progress += delta;
    return 0;
  }
}