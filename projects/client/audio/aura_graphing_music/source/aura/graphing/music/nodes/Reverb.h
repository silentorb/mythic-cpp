#pragma once

#include <signal_graph/Node.h>
#include <signal_graph/Temporary_Node.h>
#include "Delay.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Reverb_Data {
          float original;
          std::vector<float> const *buffer;
          float output;
      };
      
      template<typename Externals>
      class Reverb_Instance : public signal_graph::Node_Instance<Externals, Reverb_Data> {

      public:
          Reverb_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals, Reverb_Data>(externals) {}

          virtual void update(Externals &externals) override {
            auto &buffer = *data.buffer;
            data.output = data.original ;//+ buffer[buffer.size() - 1];// * utility::to_db(0.5f);
//            data.output = buffer[buffer.size() - 1];// * utility::to_db(0.5f);
          }
      };

      NODE_TEMPLATE
      Node Reverb(const Node &signal) {
        auto delay = Delay(signal);

        return Reverb_Instance<Default_Externals>:: create_node(
                    {
            new Input<float>(signal),
            new Input<std::vector<float> *>(delay),
            new Output<float>(),
          });
      }

      NODE_TEMPLATE
      Node Reverb() {
        return Reverb POSSIBLE_TEMPLATE(create_temporary());
      }
    }
  }
}