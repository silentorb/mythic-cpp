#pragma once

#include <signal_graph/Node.h>

using namespace signal_graph;

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Delay_Data {
          float input;
          std::vector<float> const *output;
          std::vector<float> buffer;
      };

      template<typename Externals>
      class Delay_Internal : public Node_Instance<Externals, Delay_Data> {
      public:
          Delay_Internal(Externals &externals) : Node_Instance(externals) {}

          virtual void update(Externals &externals) override {
            auto &buffer = data.buffer;
            if (buffer.size() == 0) {
              buffer.resize(externals.get_engineer().get_sample_rate() * 2);
              data.output = &buffer;
            }
            else {
              std::move(buffer.begin(), buffer.end() - 1, buffer.begin() + 1);
            }
            buffer[0] = data.input;
          }
      };

      Node Delay(const Node &signal) {
        return Delay_Internal<Delay_Data>::create_node(
          {
            new Input<float>(signal),
            new Output<std::vector<float> const *>(),
          });
      }

      Node Delay(const External_Base &engineer) {
        return Delay(Node::create_empty());
      }
    }
  }
}