#pragma once
#include "dllexport.h"
#include <cstdint>

namespace aura {

  struct MYTHIC_EXPORT Time_Signature {
      int8_t upper;
      int8_t lower;
  };

  const float quarter_note = (float)1;
  const float eigth_note = (float)1 / 2;
}
