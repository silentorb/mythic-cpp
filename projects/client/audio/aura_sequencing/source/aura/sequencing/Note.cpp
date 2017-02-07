#include "Note.h"

namespace aura {
  namespace sequencing {

    unsigned long current_id = 0;

    Note::Note(const Pitch &pitch, float start, float duration) :
      pitch(&pitch), start(start), duration(duration),
//      id(current_id++),
      frequency(pitch.frequency) {

    }

//  Note::Note(float frequency, float start, float duration) :
//    frequency(frequency), start(start), duration(duration), pitch(nullptr), id(current_id++) {
//
//  }
  }
}