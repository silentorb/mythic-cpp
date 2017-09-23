#pragma once

#include "signal_graph/Node.h"
#include <cmath>
#include <signal_graph/default_externals.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      template<typename Externals>
      class Clip_Instance : public signal_graph::Node_Instance<Externals> {
          float signal;
          float max;
          float output;
      public:
          Clip_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals>(externals) {}

          virtual void update(Externals &externals) override {
            if (signal > max)
              output = max;
            else if (signal < -max)
              output = -max;
            else
              output = signal;
          }

          virtual const void *get_data() override {
            return &signal;
          }
      };

      NODE_TEMPLATE
      signal_graph::Node Clip(const signal_graph::Node &signal, const signal_graph::Node &max) {
        return Clip_Instance<Default_Externals>::create_node(
          {
            new signal_graph::Input<float>(signal),
            new signal_graph::Input<float>(max),
            new signal_graph::Output<float>(),
          });
      }

      NODE_TEMPLATE
      signal_graph::Node Clip(const signal_graph::Node &max) {
        return Clip POSSIBLE_TEMPLATE(signal_graph::Node::create_empty(), max);
      }
    }
  }
}