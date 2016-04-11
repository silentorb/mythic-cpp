#include "Note.h"

namespace aura {

  Note::Note(const Pitch &pitch, float start, float duration) :
    pitch(&pitch), start(start), duration(duration), frequency(pitch.frequency) {

  }

  Note::Note(float frequency, float start, float duration) :
    frequency(frequency), start(start), duration(duration), pitch(nullptr) {

  }

}