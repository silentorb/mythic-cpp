#pragma once

#include "dllexport.h"
#include "Key.h"

namespace aura {

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

      Chord(Key key, Chord_Type type = Chord_Type::major) :
        key(key), type(type) { }
  };

  struct Chord_Instance {
      Chord chord;
      float duration;
      Transpose_Direction direction;

      Chord_Instance(const Chord &chord, float duration = 1,
                     Transpose_Direction direction = Transpose_Direction::incidental) :
        chord(chord), duration(duration), direction(direction) { }

      Chord_Instance(Key key, Chord_Type type, float duration = 1,
                     Transpose_Direction direction = Transpose_Direction::incidental) :
        chord(key, type), duration(duration), direction(direction) { }
  };

  namespace chords {
    const Chord c_major = {Key::C};
    const Chord c_minor = {Key::C, Chord_Type::minor};
  }

  class Conductor;
}