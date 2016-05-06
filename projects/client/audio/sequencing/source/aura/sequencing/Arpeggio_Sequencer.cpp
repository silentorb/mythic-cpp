#include "Arpeggio_Sequencer.h"

namespace aura {

  const Pitch &Arpeggio_Sequencer::transpose(Pitch &pitch, const Chord_Instance &chord) {
    const int baseline =  static_cast<int>(Key::C);
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

  const Note &Arpeggio_Sequencer::get_note(int index, Conductor &conductor)  {
    auto &pitch = transpose(arpeggio->at(index), conductor.get_chord());
    return_note = Note(pitch, index * beats_per_note, beats_per_note);
    return return_note;
  }


}