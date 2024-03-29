#pragma once

#include <cstdint>

namespace aura {
  namespace sequencing {

    struct Time_Signature {
        int8_t upper;
        int8_t lower;

        Time_Signature(int8_t upper, int8_t lower) : upper(upper), lower(lower) { }
    };

    const float whole_note = 4;
    const float half_note = 2;
    const float quarter_note = (float) 1;
    const float eighth_note = (float) 1 / 2;
    const float sixteenth_note = (float) 1 / 4;
  }
}