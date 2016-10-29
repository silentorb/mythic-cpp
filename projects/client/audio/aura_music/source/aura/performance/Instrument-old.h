#pragma once

#include "Musical_Stroke.h"
#include <aura/sequencing/Note.h>
#include "commoner/dllexport.h"

namespace aura {

  class MYTHIC_EXPORT Instrument {
  public:
      virtual Musical_Stroke *generate_stroke(const Note &note) = 0;

      virtual ~Instrument() { }
  };
}
