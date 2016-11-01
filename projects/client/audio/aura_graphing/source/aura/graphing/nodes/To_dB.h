#pragma once

#include "signal_graph/Node.h"
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct To_dB_Data {
          float input;
          float output;
      };

      signal_graph::Node To_dB(const signal_graph::Node & source) {
        return signal_graph::Node(
          NODE_ID("To_dB")
          {
            new signal_graph::Input<float>(source),
            new signal_graph::Output<float>(),
          },
          [](void *raw_data, const signal_graph::Externals&externals) {
            auto &data = *(To_dB_Data *) raw_data;
            data.output = std::pow(data.input, 2);
          });
      }

      signal_graph::Node To_dB() {
        return To_dB(signal_graph::Node::create_empty());
      }
    }
  }
}