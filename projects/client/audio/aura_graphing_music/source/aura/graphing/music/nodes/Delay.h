#pragma once

#include <signal_graph/Node.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      signal_graph::Node Delay(const signal_graph::Node &signal, const signal_graph::External &engineer);

      signal_graph::Node Delay(const signal_graph::External &engineer);
    }
  }
}