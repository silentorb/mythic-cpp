#pragma once
#include "dllexport.h"
#include <cstdint>

namespace aura {

  struct MYTHIC_EXPORT Time_Signature {
      int8_t upper;
      int8_t lower;

      Time_Signature(int8_t upper, int8_t lower) : upper(upper), lower(lower) { }
  };

  const float whole_note = 4;
  const float half_note = 2;
  const float quarter_note = (float)1;
  const float eigth_note = (float)1 / 2;
  const float sixteenth_note = (float)1 / 4;
}
