#pragma once

#include "commoner/dllexport.h"
#include "Chord.h"
#include <vector>

using namespace std;

namespace aura {
  namespace sequencing {

    using Chord_Structure = std::vector<Chord_Event>;

//    class Chord_Structure {
//        vector<Chord_Event> chords;
//        float measures = 0;
//
//    public:
//
//        Chord_Structure() {}
//
//        Chord_Structure(initializer_list<Chord_Event> initializer);
//
//        void set_chords(initializer_list<Chord_Event> initializer);
//
//        const vector<Chord_Event> &get_chords() const {
//          return chords;
//        }
//
//        float get_measures() const {
//          return measures;
//        }
//
////        void update(Conductor &conductor, float start, float end);
//    };
  }
}