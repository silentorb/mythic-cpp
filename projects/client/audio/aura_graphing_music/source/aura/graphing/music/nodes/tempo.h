#pragma once

#include "signal_graph/Node.h"

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  namespace graphing {
    namespace nodes {

      signal_graph::Node Seconds_Tempo(const sequencing::Conductor &conductor);
    }
  }
}