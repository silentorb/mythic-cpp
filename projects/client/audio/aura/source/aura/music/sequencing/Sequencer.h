#pragma once

#include "dllexport.h"
#include "Note.h"
#include "Conductor.h"

namespace aura {

  class MYTHIC_EXPORT Sequencer {
  public:
      virtual float get_beats() const = 0;
      virtual int size() const = 0;
      virtual const Note &get_note(int index, Conductor & conductor) = 0;
  };
}