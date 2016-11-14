#pragma once

#include "signal_graph/Node.h"
#include <cmath>
#include <aura/processing/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {


      template<typename Externals>
      class To_dB_Instance : public signal_graph::Node_Instance<Externals> {
          float input;
          float output;

      public:
          To_dB_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals>(externals) {}

          virtual void update(Externals &externals) override {
            output = utility::to_db(input);
          }

          virtual const void *get_data() override {
            return &input;
          }
      };

      NODE_TEMPLATE
      signal_graph::Node To_dB(const signal_graph::Node &source) {
        return To_dB_Instance<Default_Externals>::create_node(
          {
            new signal_graph::Input<float>(source),
            new signal_graph::Output<float>(),
          });
      }

      NODE_TEMPLATE
      signal_graph::Node To_dB() {
        return To_dB POSSIBLE_TEMPLATE(signal_graph::Node::create_empty());
      }

      signal_graph::Node dB(float value) {
        return signal_graph::Node(utility::to_db(value));
      }

    }
  }
}