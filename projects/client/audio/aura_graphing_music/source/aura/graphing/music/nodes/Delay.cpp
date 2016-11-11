#include <aura/engineering/Engineer.h>
#include "Delay.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Delay_Data {
          float input;
//          float output;
          std::vector<float> const *output;
          std::vector<float> buffer;
      };

      signal_graph::Node Delay(const signal_graph::Node &signal, const signal_graph::External &engineer) {
        return signal_graph::create_node<Delay_Data>(
          NODE_ID("Reverb")
          {
            new signal_graph::Input<float>(signal),
            new signal_graph::Output<std::vector<float> const *>(),
          },
          [&engineer](void *raw_data, const signal_graph::Externals &externals) {
            auto &data = *(Delay_Data *) raw_data;
            auto &buffer = data.buffer;
            if (buffer.size() == 0) {
              auto &engineer_value = externals.get_external<engineering::Engineer>(engineer);
              buffer.resize(engineer_value.get_sample_rate());
            }
            std::move(buffer.begin(), buffer.end() - 1, buffer.begin() + 1);
            buffer[0] = data.input;
//            data.output = buffer[buffer.size() - 1];
            data.output = &buffer;
          });
      }

      signal_graph::Node Delay(const signal_graph::External &engineer) {
        return Delay(signal_graph::Node::create_empty(), engineer);
      }
    }
  }
}