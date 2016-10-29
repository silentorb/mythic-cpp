#pragma once

#include "commoner/dllexport.h"
#include "Chord.h"
#include <vector>

using namespace std;

namespace aura {
  namespace sequencing {

  class MYTHIC_EXPORT Chord_Structure {
      vector<Chord_Instance> chords;
      float measures = 0;

  public:

      Chord_Structure() { }

      Chord_Structure(initializer_list<Chord_Instance> initializer);

      void set_chords(initializer_list<Chord_Instance>initializer);

      const vector<Chord_Instance> &get_chords() const {
            return chords;
      }

      float get_measures() const {
            return measures;
      }
  };
}}