#include "Note.h"

namespace aura {
  namespace sequencing {

    unsigned long current_id = 0;

    Note::Note(const Pitch &pitch, Beats start, Beats duration, float velocity) :
      pitch(&pitch), start(start), duration(duration),
//      id(current_id++),
      frequency(pitch.frequency), velocity(velocity) {

    }

//  Note::Note(float frequency, float start, float duration) :
//    frequency(frequency), start(start), duration(duration), pitch(nullptr), id(current_id++) {
//
//  }
  }
}