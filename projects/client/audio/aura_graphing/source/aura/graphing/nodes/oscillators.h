#pragma once

#include "signal_graph/Node.h"
#include <cmath>
#include <math/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      signal_graph::Node Sine_Wave_With_Position_Source(const signal_graph::Node &position_source);
      signal_graph::Node Sine_Wave(const signal_graph::Node &frequency, const signal_graph::External_Base &engineer);

      signal_graph::Node Saw_Wave_With_Position_Source(const signal_graph::Node &position_source);
      signal_graph::Node Saw_Wave(const signal_graph::Node &frequency, const signal_graph::External_Base &engineer);

    }
  }
}