#include "Chord_Structure.h"
#include "Conductor.h"
#include "utility.h"

namespace aura {
  namespace sequencing {

    Chord_Structure::Chord_Structure(initializer_list<Chord_Instance> initializer) : chords(initializer) {
      for (auto &chord: chords) {
        measures += chord.duration;
      }
    }

    void Chord_Structure::set_chords(initializer_list<Chord_Instance> initializer) {
      for (auto &chord: initializer) {
        chords.push_back(chord);
        measures += chord.duration;
      }
    }

    void Chord_Structure::update(Conductor &conductor, float start, float end) {
      if (end == start)
        return;

      start *= measures;
      end *= measures;

      float offset = 0;
      for (auto &chord: chords) {
        offset += chord.duration;
        if (is_inside(offset, start, end)) {
          conductor.set_chord(chord);
        }
      }
    }
  }
}