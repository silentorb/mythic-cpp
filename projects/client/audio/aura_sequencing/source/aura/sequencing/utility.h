#pragma once
#include "Pitch.h"
#include "Chord.h"

namespace aura {
  namespace sequencing {

    inline bool is_inside(float offset, float start, float end) {
      return end > start
      ? offset >= start && offset < end
      : offset >= start || offset < end;
    }

    const Pitch &transpose(const Pitch &pitch, const Chord &chord);

  }
}