#include "Arpeggio_Sequencer.h"

namespace aura {

  Pitch Arpeggio_Sequencer::transpose(Pitch &pitch, const Chord &chord) {
    int offset = static_cast<int>(chord.key) - static_cast<int>(Key::C);
    auto index = pitch.index + offset;
    if (chord.type == Chord_Type::minor && pitch.key == Key::E) {
      --index;
    }
    return Pitches[index];
  }

  const Note &Arpeggio_Sequencer::get_note(int index, Conductor &conductor)  {
    auto pitch = transpose(arpeggio->at(index), conductor.get_chord());
    return_note = Note(pitch, index * beats_per_note, beats_per_note);
    return return_note;
  }


}