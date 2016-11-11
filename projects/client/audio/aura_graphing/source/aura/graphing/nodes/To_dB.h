#pragma once

#include "signal_graph/Node.h"
#include <cmath>
#include <aura/utility/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct To_dB_Data {
          float input;
          float output;
      };

      signal_graph::Node To_dB(const signal_graph::Node & source);

      signal_graph::Node To_dB();
      signal_graph::Node dB(float value);
    }
  }
}