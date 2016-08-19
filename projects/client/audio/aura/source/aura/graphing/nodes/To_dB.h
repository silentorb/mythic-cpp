#pragma once

#include <aura/graphing/Node.h>
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct To_dB_Data {
          float input;
          float output;
      };

      Node To_dB(const Node & source) {
        return Node(
          NODE_ID("To_dB")
          {
            new Input<float>(source),
            new Output<float>(),
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(To_dB_Data *) raw_data;
            data.output = std::pow(data.input, 2);
          });
      }

      Node To_dB() {
        return To_dB(Node::create_empty());
      }

      float to_db(float value) {
        return std::pow(value, 2);
      }
    }
  }
}