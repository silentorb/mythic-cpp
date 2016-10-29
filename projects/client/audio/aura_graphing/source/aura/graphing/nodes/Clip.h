#pragma once

#include "../Node.h"
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Clip_Data {
          float signal;
          float max;
          float output;
      };

      Node Clip(const Node &signal, const Node &max);

      Node Clip(const Node &max);
    }
  }
}