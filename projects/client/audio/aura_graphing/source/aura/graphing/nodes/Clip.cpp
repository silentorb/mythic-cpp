#include "Clip.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      signal_graph::Node Clip(const signal_graph::Node &signal, const signal_graph::Node &max) {
        return signal_graph::Node(
          NODE_ID("Clip")
          {
            new signal_graph::Input<float>(signal),
            new signal_graph::Input<float>(max),
            new signal_graph::Output<float>(),
          },
          [](void *raw_data, const signal_graph::Externals&externals) {
            auto &data = *(Clip_Data *) raw_data;
            if (data.signal > data.max)
              data.output = data.max;
            else if (data.signal < -data.max)
              data.output = -data.max;
            else
              data.output = data.signal;
          });
      }

      signal_graph::Node Clip(const signal_graph::Node &max) {
        return Clip(signal_graph::Node::create_empty(), max);
      }
    }
  }
}