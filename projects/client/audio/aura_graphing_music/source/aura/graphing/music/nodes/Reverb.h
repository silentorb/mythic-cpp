#pragma once

#include <signal_graph/Node.h>
#include <signal_graph/Temporary_Node.h>
#include "Delay.h"
#include <signal_graph/default_externals.h>

namespace aura {
  namespace graphing {
    namespace nodes {


      template<typename Externals>
      class Reverb_Instance : public signal_graph::Node_Instance<Externals> {
          float original;
          std::vector<float> const *buffer;
          float output;

      public:
          Reverb_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals>(externals) {}

          virtual void update(Externals &externals) override {
            auto &buffer = *buffer;
            output = original;//+ buffer[buffer.size() - 1];// * utility::to_db(0.5f);
//            output = buffer[buffer.size() - 1];// * utility::to_db(0.5f);
          }

          virtual const void *get_data() override {
            return &original;
          }
      };

      NODE_TEMPLATE
      Node Reverb(const Node &signal) {
        auto delay = Delay<Default_Externals>(signal);

        return Reverb_Instance<Default_Externals>::create_node(
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