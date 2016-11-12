#pragma once

#include <signal_graph/Node.h>

namespace aura {
  namespace engineering {
    class Engineer;
  }

  namespace graphing {
    namespace nodes {

      signal_graph::Node Reverb(const signal_graph::Node &signal,
                                const signal_graph::External_Input<aura::engineering::Engineer> &engineer);

      signal_graph::Node Reverb(const signal_graph::External_Input<aura::engineering::Engineer> &engineer);
    }
  }
}