#include "oscillators.h"
#include "Loop_Node.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Oscillator_Data {
          float position;
          float output;
      };

      signal_graph::Node Sine_Wave_With_Position_Source(const signal_graph::Node &position_source) {
        return signal_graph::Node(
          NODE_ID("Sine_Wave")
          {
            new signal_graph::Input<float>(position_source),
            new signal_graph::Output<float>,
          },
          [](void *raw_data, const signal_graph::Externals&externals) {
            auto &data = *(Oscillator_Data *) raw_data;
            data.output = sin(data.position * 2 * Pi);
          });
      }

      signal_graph::Node Sine_Wave(const signal_graph::Node &frequency, const signal_graph::External &engineer) {
        return Sine_Wave_With_Position_Source(Loop_Node(frequency, engineer));
      }

      signal_graph::Node Saw_Wave_With_Position_Source(const signal_graph::Node &position_source) {
        return signal_graph::Node(
          NODE_ID("Saw_Wave")
          {
            new signal_graph::Input<float>(position_source),
            new signal_graph::Output<float>,
          },
          [](void *raw_data, const signal_graph::Externals&externals) {
            auto &data = *(Oscillator_Data *) raw_data;
            data.output = std::abs(fmod(data.position, 2) - 1);
          });
      }

      signal_graph::Node Saw_Wave(const signal_graph::Node &frequency, const signal_graph::External &engineer) {
        return Saw_Wave_With_Position_Source(Loop_Node(frequency, engineer));
      }
    }
  }
}

