#include "Conductor.h"
#include "Event_Recorder.h"

namespace aura {

  void Conductor::commence() {
//    set_chord(get_current_chord_structure().get_chords()[0]);
  }

  void Conductor::set_chord(const Chord_Instance chord, float offset, float start, float end) {
    this->chord = chord;
    if (recorder)
      recorder->add_event(new Chord_Event(chord, offset, start, end));
  }


}