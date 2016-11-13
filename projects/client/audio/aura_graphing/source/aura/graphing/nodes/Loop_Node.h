#pragma once

#include "signal_graph/Node.h"
#include <aura/processors/Loop.h>
#include <signal_graph/default_externals.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      template<typename Externals>
      class Loop_Instance : public signal_graph::Node_Instance<Externals> {
          Loop loop;
          float frequency;
          float output;

      public:
          Loop_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals>(externals),
            loop(externals.get_engineer().get_sample_rate()) {

          }

          virtual void update(Externals &externals) override {
            loop.set_frequency(frequency);
            output = loop.next();
          }

          virtual const void *get_data() override {
            return &frequency;
          }
      };

      NODE_TEMPLATE
      signal_graph::Node Loop_Node(const signal_graph::Node &frequency_source) {
        return Loop_Instance<Default_Externals>::create_node(
          {
            new signal_graph::Input<float>(frequency_source),
            new signal_graph::Output<float>(),
          });
      }
    }
  }
}