#include "Sequence.h"

namespace aura {
  namespace sequencing {


    void Sequence::add_note(const Note &note) {
      notes.push_back(note);
      auto end = note.get_start() + note.get_duration();
      if (end > beats)
        beats = end;
    }

    void Sequence::add_notes(initializer_list<const Note> initializer) {
      for (auto &note: initializer) {
        add_note(note);
      }
    }

    void Sequence::add_notes(float offset, float note_length, initializer_list<const Note> initializer) {
      for (auto &note: initializer) {
        add_note(Note(*note.get_pitch(), note.get_start() + offset, note_length));
      }
    }

    void Sequence::generate_notes(Note_Consumer &consumer, Conductor &conductor) {
      for(auto & note: notes) {
        consumer.add_note(note);
      }
    }

  }
}