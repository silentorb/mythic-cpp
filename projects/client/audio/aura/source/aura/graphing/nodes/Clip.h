#pragma once

#include <aura/graphing/Node.h>
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Clip_Data {
          float signal;
          float max;
          float output;
      };

      Node Clip(const Node &signal, const Node &max) {
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