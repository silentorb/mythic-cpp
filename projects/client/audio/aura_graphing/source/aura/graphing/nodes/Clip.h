#pragma once

#include "signal_graph/Node.h"
#include <cmath>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Clip_Data {
          float signal;
          float max;
          float output;
      };
//
//      signal_graph::Node Clip(const signal_graph::Node &signal, const signal_graph::Node &max);
//
//      signal_graph::Node Clip(const signal_graph::Node &max);

      template<typename Externals>
      class Clip_Instance : public signal_graph::Node_Instance<Externals, Clip_Data> {

      public:
          Clip_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals, Clip_Data>(externals) {}

          virtual void update(Externals &externals) override {
            if (data.signal > data.max)
              data.output = data.max;
            else if (data.signal < -data.max)
              data.output = -data.max;
            else
              data.output = data.signal;
          }
      };

      signal_graph::Node Clip(const signal_graph::Node &signal, const signal_graph::Node &max) {
        return Clip_Instance::create_node(
          {
            new signal_graph::Input<float>(signal),
            new signal_graph::Input<float>(max),
            new signal_graph::Output<float>(),
          });
      }

      signal_graph::Node Clip(const signal_graph::Node &max) {
        return Clip(signal_graph::Node::create_empty(), max);
      }
    }
  }
}