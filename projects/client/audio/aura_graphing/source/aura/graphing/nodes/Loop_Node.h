#pragma once

#include "signal_graph/Node.h"
#include <aura/processors/Loop.h>

namespace aura {
  namespace graphing {
    namespace nodes {

//      signal_graph::Node Loop_Node(const signal_graph::Node &frequency_source, const signal_graph::External_Base &engineer);

      struct Oscillator_Data {
          float frequency;
          float output;
      };

      template<typename Externals>
      class Oscillator_Instance : public signal_graph::Node_Instance<Externals, Oscillator_Data> {
          Loop loop;

      public:
          Oscillator_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals, Oscillator_Data>(externals),
            loop(externals.get_engineer().get_sample_rate()) {

          }

          virtual void update(Externals &externals) override {
            loop.set_frequency(data.frequency);
            data.output = loop.next();
          }
      };

      signal_graph::Node Loop_Node(const signal_graph::Node &frequency_source) {
        return Oscillator_Instance::create_node(
          {
            new signal_graph::Input<float>(frequency_source),
            new signal_graph::Output<float>(),
          });
      }
    }
  }
}