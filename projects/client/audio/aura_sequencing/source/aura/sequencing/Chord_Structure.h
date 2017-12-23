#pragma once


#include "Chord.h"
#include <vector>

namespace aura {
  namespace sequencing {

    struct Chord_Event_Without_Duration {
        Chord chord;
        Transpose_Direction direction;

        Chord_Event_Without_Duration(Key key, Chord_Type type,
                                     Transpose_Direction direction = Transpose_Direction::incidental) :
          chord(key, type), direction(direction) {}
    };

    class Chord_Structure : public std::vector<Chord_Event> {
    public:
        Chord_Structure(std::initializer_list<Chord_Event> initializer) :
          std::vector<Chord_Event>(initializer) {}

        Chord_Structure(std::initializer_list<Chord_Event_Without_Duration> initializer, const Beats chord_duration) {
          reserve(initializer.size());
          for (auto &item : initializer) {
            emplace_back(item.chord, chord_duration, item.direction);
          }
        }
    };
  }
}