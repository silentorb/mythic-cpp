#include "Clip.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      Node Clip(const aura::graphing::Node &signal, const aura::graphing::Node &max) {
        return Node(
          NODE_ID("Clip")
          {
            new Input<float>(signal),
            new Input<float>(max),
            new Output<float>(),
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(Clip_Data *) raw_data;
            if (data.signal > data.max)
              data.output = data.max;
            else if (data.signal < -data.max)
              data.output = -data.max;
            else
              data.output = data.signal;
          });
      }

      Node Clip(const Node &max) {
        return Clip(Node::create_empty(), max);
      }
    }
  }
}