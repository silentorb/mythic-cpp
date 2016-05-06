#pragma once

#include "sequencing_export.h"

namespace aura {

  enum class Key : int {
      A = 0,
      AS = 1,
      BF = 1,
      B = 2,
      C = 3,
      CS = 4,
      DF = 4,
      D = 5,
      DS = 6,
      EF = 6,
      E = 7,
      F = 8,
      FS = 9,
      GF = 9,
      G = 10,
      GS = 11,
      AF = 11
  };

  SEQUENCING_EXPORT const char *get_keyname(Key key);
}