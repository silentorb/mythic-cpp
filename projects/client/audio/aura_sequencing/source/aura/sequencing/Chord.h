#pragma once

#include "Key.h"
#include "Beats.h"

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

    class Chord_Event {
        Chord chord;
        Beats offset;
        Transpose_Direction direction;

    public:
        Chord_Event(const Chord &chord, Beats offset) : chord(chord), offset(offset) {}

        Chord_Event(Key key, Chord_Type type, Beats offset,
                    Transpose_Direction direction = Transpose_Direction::incidental) :
          chord(key, type), offset(offset), direction(direction) {}

        const Chord &get_chord() const {
          return chord;
        }

        Beats get_offset() const {
          return offset;
        }
    };

    namespace chords {
      const Chord c_major = {Key::C};
      const Chord c_minor = {Key::C, Chord_Type::minor};
    }

    class Chord_Source {
    public:
        virtual const Chord get_chord() = 0;
    };
  }
}