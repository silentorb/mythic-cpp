#pragma once

#include <signal_graph/Node.h>
#include <signal_graph/default_externals.h>

using namespace signal_graph;

namespace aura {
  namespace graphing {
    namespace nodes {

      template<typename Externals>
      class Delay_Internal : public Node_Instance<Externals> {
          float input;
          std::vector<float> const *output;
          std::vector<float> buffer;

      public:
          Delay_Internal(Externals &externals) : Node_Instance<Externals>(externals) {}

          virtual void update(Externals &externals) override {
            auto &buffer = buffer;
            if (buffer.size() == 0) {
              buffer.resize(externals.get_engineer().get_sample_rate() * 2);
              output = &buffer;
            }
            else {
              std::move(buffer.begin(), buffer.end() - 1, buffer.begin() + 1);
            }
            buffer[0] = input;
          }

          virtual const void *get_data() override {
            return &input;
          }
      };

      NODE_TEMPLATE
      Node Delay(const Node &signal) {
        return Delay_Internal<Default_Externals>::create_node(
          {
            new Input<float>(signal),
            new Output<std::vector<float> const *>(),
          });
      }

      NODE_TEMPLATE
      Node Delay(const External_Base &engineer) {
        return Delay POSSIBLE_TEMPLATE(Node::create_empty());
      }
    }
  }
}