#include "Chord.h"

namespace aura {
  namespace sequencing {


  const char *keynames[] = {
    "A",
    "A#",
    "B",
    "C",
    "C#",
    "D",
    "D#",
    "E",
    "F",
    "F#",
    "G",
    "G#"
  };

  const char *get_keyname(Key key) {
    int index = static_cast<int>(key);
    return keynames[index];
  }
}}