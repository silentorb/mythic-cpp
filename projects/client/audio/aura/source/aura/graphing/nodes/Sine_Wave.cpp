#include "Sine_Wave.h"
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Sine_Wave_Data {
          float position;
          float output;
      };

      Node Sine_Wave_With_Position_Source(const Node &position_source) {
        return Node(
          NODE_ID("Sine_Wave")
          {
            new Input<float>(position_source),
            new Output<float>,
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(Sine_Wave_Data *) raw_data;
            data.output = sin(data.position * 2 * Pi);
          });
      }

      Node Sine_Wave(const Node &frequency) {
        return Sine_Wave_With_Position_Source(Loop_Node(frequency));
      }
    }
  }
}

