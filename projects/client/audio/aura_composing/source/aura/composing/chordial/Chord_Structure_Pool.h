#pragma once

#include <randomly/Dice.h>
#include "Chord_Structure_Source.h"

namespace aura {
  namespace composing {
    namespace chordial {

      class Chord_Structure_Pool : public Chord_Structure_Source {
          randomly::Dice &dice;
          std::vector<sequencing::Chord_Structure> structures;

      public:
          Chord_Structure_Pool(randomly::Dice &dice,
                               const std::initializer_list<sequencing::Chord_Structure> &structures) :
            dice(dice), structures(structures) {}

          sequencing::Chord_Structure get_chord_structure(const sequencing::Beats &start) override {
            return dice.get_item(structures);
          }
      };
    }
  }
}