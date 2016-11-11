#include "Reverb.h"
#include "Delay.h"
#include <aura/engineering/Engineer.h>

using namespace signal_graph;
using namespace std;

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Reverb_Data {
          float original;
          std::vector<float> const *input;
          float output;
      };

      Node Reverb(const Node &signal, const External &engineer) {
        auto delay = Delay(signal, engineer);

        return create_node<Reverb_Data>(
          NODE_ID("Reverb")
          {
            new Input<float>(signal),
            new Input<vector<float> *>(delay),
            new Output<float>(),
          },
          [&engineer](void *raw_data, const Externals &externals) {
            auto &data = *(Reverb_Data *) raw_data;
            auto &buffer = *data.input;
            data.output = data.original + buffer[buffer.size() - 1];
          });
      }

      Node Reverb(const External &engineer) {
        return Reverb(Node::create_empty(), engineer);
      }
    }
  }
}