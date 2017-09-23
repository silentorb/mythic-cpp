#pragma once

#include "signal_graph/Node.h"

namespace aura {
  namespace sequencing {
    class Conductor;
  }

  namespace graphing {
    namespace nodes {

      struct Tempo_Data {
          float output;
      };

      template<typename Externals>
      class Tempo_Instance : public signal_graph::Node_Instance<Externals, Tempo_Data> {

      public:
          Tempo_Instance(Externals &externals) :
            signal_graph::Node_Instance<Externals, Tempo_Data>(externals) {}

          virtual void update(Externals &externals) override {
            data.output = externals.get_conductor().get_seconds_tempo();
          }
      };

      NODE_TEMPLATE
      signal_graph::Node Seconds_Tempo() {
        return Tempo_Instance<Default_Externals>::create_node(
          {
            new signal_graph::Output<float>(),
          });
      }
    }
  }
}