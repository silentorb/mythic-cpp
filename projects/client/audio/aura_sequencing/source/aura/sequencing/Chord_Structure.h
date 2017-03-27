#pragma once

#include "commoner/dllexport.h"
#include "Chord.h"
#include <vector>

using namespace std;

namespace aura {
  namespace sequencing {
//
//    struct Chord_Instance {
//        Chord chord;
//        Beats duration;
//        Transpose_Direction direction;
//
//    public:
////        Chord_Instance(const Chord &chord, Beats offset) : chord(chord), duration(duration) {}
//
//        Chord_Instance(Key key, Chord_Type type, Beats duration = 4,
//                       Transpose_Direction direction = Transpose_Direction::incidental) :
//          chord(key, type), duration(duration), direction(direction) {}
//    };

//    using Chord_Structure = std::vector<Chord_Event>;


    struct Chord_Event_Without_Duration {
        Chord chord;
        Transpose_Direction direction;

        Chord_Event_Without_Duration(Key key, Chord_Type type,
                                     Transpose_Direction direction = Transpose_Direction::incidental) :
          chord(key, type), direction(direction) {}
    };


    class Chord_Structure : public std::vector<Chord_Event> {
//
    public:
        Chord_Structure(initializer_list<Chord_Event> initializer) :
          std::vector<Chord_Event>(initializer) {}

        Chord_Structure(initializer_list<Chord_Event_Without_Duration> initializer, const Beats chord_duration) {
          reserve(initializer.size());
          for (auto &item : initializer) {
            emplace_back(item.chord, chord_duration, item.direction);
          }
        }
    };

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