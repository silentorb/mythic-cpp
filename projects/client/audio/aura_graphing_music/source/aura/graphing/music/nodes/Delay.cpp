#include <aura/engineering/Engineer.h>
#include "Delay.h"

using namespace signal_graph;

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Delay_Data {
          float input;
          std::vector<float> const *output;
          std::vector<float> buffer;
      };

      Node Delay(const Node &signal, const External_Base &engineer, const External_Output<) {
        return create_node<Delay_Data>(
          NODE_ID("Delay")
          {
            new Input<float>(signal),
            new Output<std::vector<float> const *>(),
            new Internal<std::vector<float> const *>(),
          },
          [&engineer](void *raw_data, const Externals &externals) {
            auto &data = *(Delay_Data *) raw_data;
            auto &buffer = data.buffer;
            if (buffer.size() == 0) {
              auto &engineer_value = externals.get_external<engineering::Engineer>(engineer);
              buffer.resize(engineer_value.get_sample_rate() * 2);
              data.output = &buffer;

            }
            else {
              std::move(buffer.begin(), buffer.end() - 1, buffer.begin() + 1);
            }
            buffer[0] = data.input;
          });
      }

      Node Delay(const External_Base &engineer) {
        return Delay(Node::create_empty(), engineer);
      }
    }
  }
}