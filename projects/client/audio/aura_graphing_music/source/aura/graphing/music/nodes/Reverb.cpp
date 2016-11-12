#include "Reverb.h"
#include "Delay.h"
#include <aura/engineering/Engineer.h>
#include <signal_graph/Temporary_Node.h>
#include <aura/utility/utility.h>

using namespace signal_graph;
using namespace std;

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Reverb_Data {
          float original;
          std::vector<float> const *buffer;
          float output;
      };

      Node Reverb(const Node &signal, const External_Input<engineering::Engineer> &engineer) {
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
            auto &buffer = *data.buffer;
            data.output = data.original ;//+ buffer[buffer.size() - 1];// * utility::to_db(0.5f);
//            data.output = buffer[buffer.size() - 1];// * utility::to_db(0.5f);
          });
      }

      Node Reverb(const External_Input<engineering::Engineer> &engineer) {
        return Reverb(create_temporary(), engineer);
      }
    }
  }
}