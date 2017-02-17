#pragma once

#include "commoner/dllexport.h"
#include "Key.h"

namespace aura {
  namespace sequencing {

    enum Chord_Type {
        major,
        minor,
        diminished,
        augmented,
    };

    enum class Transpose_Direction {
        down,
        up,
        incidental,
        nearest
    };

    struct Chord {
        Key key;
        Chord_Type type;

        Chord(Key key = Key::A, Chord_Type type = Chord_Type::major) :
          key(key), type(type) {}

        bool operator==(const Chord &other) const {
          return key == other.key && type == other.type;
        }

        bool operator!=(const Chord &other) const {
          return key != other.key || type != other.type;
        }
    };

    struct Chord_Instance {
        Chord chord;
        float duration;
        Transpose_Direction direction;

        Chord_Instance(const Chord &chord, float duration = 1,
                       Transpose_Direction direction = Transpose_Direction::incidental) :
          chord(chord), duration(duration), direction(direction) {}

        Chord_Instance(Key key, Chord_Type type, float duration = 1,
                       Transpose_Direction direction = Transpose_Direction::incidental) :
          chord(key, type), duration(duration), direction(direction) {}
    };

    namespace chords {
      const Chord c_major = {Key::C};
      const Chord c_minor = {Key::C, Chord_Type::minor};
    }

//    class Chord_Consumer {
//    public:
//        virtual void add_chord(const Chord &chord) = 0;
//    };
//
//    class Chord_Source {
//    public:
//        virtual void generate_chords(Chord_Consumer &consumer) = 0;
//    };

    class Chord_Source {
    public:
        virtual const Chord get_chord() = 0;
    };
  }
}