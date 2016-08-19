#include "oscillators.h"
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Oscillator_Data {
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
            auto &data = *(Oscillator_Data *) raw_data;
            data.output = sin(data.position * 2 * Pi);
          });
      }

      Node Sine_Wave(const Node &frequency) {
        return Sine_Wave_With_Position_Source(Loop_Node(frequency));
      }

      Node Saw_Wave_With_Position_Source(const Node &position_source) {
        return Node(
          NODE_ID("Saw_Wave")
          {
            new Input<float>(position_source),
            new Output<float>,
          },
          [](const Stroke &stroke, void *raw_data) {
            auto &data = *(Oscillator_Data *) raw_data;
            data.output = std::abs(fmod(data.position, 2) - 1);
          });
      }

      Node Saw_Wave(const Node &frequency) {
        return Saw_Wave_With_Position_Source(Loop_Node(frequency));
      }
    }
  }
}

