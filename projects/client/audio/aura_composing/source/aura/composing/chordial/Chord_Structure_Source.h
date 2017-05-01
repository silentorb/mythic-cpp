#pragma once

#include <aura/sequencing/Chord_Structure.h>

namespace aura {
  namespace composing {
    namespace chordial {

      class Chord_Structure_Source {
      public:
          virtual sequencing::Chord_Structure get_chord_structure(const sequencing::Beats &start) = 0;
      };
    }
  }
}