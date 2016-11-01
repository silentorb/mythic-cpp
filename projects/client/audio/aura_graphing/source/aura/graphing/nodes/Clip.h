#pragma once

#include "signal_graph/Node.h"
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Clip_Data {
          float signal;
          float max;
          float output;
      };

      signal_graph::Node Clip(const signal_graph::Node &signal, const signal_graph::Node &max);

      signal_graph::Node Clip(const signal_graph::Node &max);
    }
  }
}