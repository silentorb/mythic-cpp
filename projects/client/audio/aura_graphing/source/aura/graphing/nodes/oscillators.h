#pragma once

#include "../Node.h"
#include <cmath>
#include <math/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      AURA_EXPORT Node Sine_Wave_With_Position_Source(const Node &position_source);
      AURA_EXPORT Node Sine_Wave(const Node &frequency);

      AURA_EXPORT Node Saw_Wave_With_Position_Source(const Node &position_source);
      AURA_EXPORT Node Saw_Wave(const Node &frequency);

    }
  }
}