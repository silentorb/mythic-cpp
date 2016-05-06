#pragma once

#include <aura/music/performance/Stroke.h>
#include <aura/sequencing/Note.h>
#include "dllexport.h"

namespace aura {

  class MYTHIC_EXPORT Instrument {
//      typedef std::function<Stroke *(const Note &note)> Instrument;
  public:
      virtual Stroke *generate_stroke(const Note &note) = 0;

  };
}
