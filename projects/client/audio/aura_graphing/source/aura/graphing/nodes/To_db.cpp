#include "To_dB.h"

using namespace signal_graph;

namespace aura {
  namespace graphing {
    namespace nodes {

      signal_graph::Node To_dB(const signal_graph::Node &source) {
        return signal_graph::Node(
          NODE_ID("To_dB")
          {
            new signal_graph::Input<float>(source),
            new signal_graph::Output<float>(),
          },
          nullptr,
          [](void *raw_data, const signal_graph::Externals &externals) {
            auto &data = *(To_dB_Data *) raw_data;
//            data.output = std::pow(data.input, 2);
            data.output = utility::to_db(data.input);
          });
      }

      signal_graph::Node To_dB() {
        return To_dB(signal_graph::Node::create_empty());
      }

      Node dB(float value) {
        return Node(utility::to_db(value));
      }
    }
  }
}