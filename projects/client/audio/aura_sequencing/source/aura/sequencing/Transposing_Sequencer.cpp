#include "Transposing_Sequencer.h"

namespace aura {
  namespace sequencing {

    const Pitch &transpose(const Pitch &pitch, const Chord_Instance &chord) {
      const int baseline = static_cast<int>(Key::C);
      const int original = static_cast<int>(chord.chord.key);
      int offset = original - baseline;

      if (chord.direction == Transpose_Direction::down) {
        if (original > baseline)
          offset -= 12;
      }

//    int offset = static_cast<int>(chord.key) - static_cast<int>(Key::C);
      auto index = pitch.index + offset;
      if (chord.chord.type == Chord_Type::minor && pitch.key == Key::E) {
        --index;
      }
      return Pitches[index];
    }

    const Note &Transposing_Sequencer::get_note(int index, Conductor &conductor) {
      auto note = source->get_note(index, conductor);
      auto &pitch = transpose(*note.get_pitch(), conductor.get_chord());
      return_note = Note(pitch, note.get_start(), note.get_duration());
      return return_note;
    }

    void Transposing_Sequencer::generate_notes(Note_Consumer &consumer, Conductor &conductor) {
      for (int i = 0; i < source->size(); ++i) {
        consumer.add_note(get_note(i, conductor));
      }
    }

  }
}