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

  struct Chord {
      Key key;
      Chord_Type type;

      Chord(Key key, Chord_Type type = Chord_Type::major) :
        key(key), type(type) { }
  };

  struct Chord_Instance {
      Chord chord;
      float duration;

      Chord_Instance(const Chord &chord, float duration = 1) : chord(chord), duration(duration) { }
      Chord_Instance(Key key, Chord_Type type, float duration = 1) : chord(key, type), duration(duration) { }
  };

  namespace chords {
    const Chord c_major = {Key::C};
    const Chord c_minor = {Key::C, Chord_Type::minor};
  }

  class Conductor;
}