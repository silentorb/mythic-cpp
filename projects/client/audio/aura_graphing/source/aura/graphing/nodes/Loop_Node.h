#pragma once

#include "signal_graph/Node.h"
#include <aura/processors/Loop.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      signal_graph::Node Loop_Node(const signal_graph::Node &frequency_source, const signal_graph::External_Base &engineer);
    }
  }
}