#include "Sequence.h"
#include "aura/music/performance/Performer.h"

namespace aura {


  void Sequence::add_note(const Note &note) {
    notes.push_back(note);
    auto end = note.get_start() + note.get_duration();
    if (end > seconds)
      seconds = end;
  }

  void Sequence::add_notes(initializer_list<Note> initializer) {
    for (auto &note: initializer) {
      add_note(note);
    }
  }

}