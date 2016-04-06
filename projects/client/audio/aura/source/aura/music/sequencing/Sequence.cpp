#include "Sequence.h"
#include "aura/music/performance/Performer.h"

namespace aura {


  void Sequence::add_note(const Note &note) {
    notes.push_back(note);
    auto end = note.get_start() + note.get_duration();
    if (end > beats)
      beats = end;
  }

  void Sequence::add_notes(initializer_list<Note> initializer) {
    for (auto &note: initializer) {
      add_note(note);
    }
  }

  void Sequence::add_notes(float offset, float note_length, initializer_list<Note> initializer) {
    for (auto &note: initializer) {
      add_note(Note(*note.get_pitch(), note.get_start() + offset, note_length));
    }
  }


}