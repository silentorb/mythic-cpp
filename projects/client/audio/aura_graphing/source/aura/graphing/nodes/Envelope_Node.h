#pragma once

#include "signal_graph/Node.h"
#include <aura/envelopes/Custom_Envelope.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Envelope_Node_Data {
          envelopes::Custom_Envelope_Instance instance;
          float output;
      };

      signal_graph::Node Envelope_Node(const std::shared_ptr<envelopes::Custom_Envelope> &envelope, const signal_graph::External &duration,
                         const signal_graph::External &progress);

      signal_graph::Node Envelope_Node(std::initializer_list<envelopes::Point> points, const signal_graph::External &duration,
                                       const signal_graph::External &progress);
    }
  }
}