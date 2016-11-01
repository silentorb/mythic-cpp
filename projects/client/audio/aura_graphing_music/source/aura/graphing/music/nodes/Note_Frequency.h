#pragma once

#include "../../../../../../signal_graph/source/signal_graph/Node.h"
#include <cmath>
#include <math/utility.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Note_Frequency_Data {
          float output;
      };

      signal_graph::Node Note_Frequency(const signal_graph::External &frequency) {
        return signal_graph::Node(
          NODE_ID("Note_Frequency")
          {
            new signal_graph::Empty_Internal([& frequency](void *raw_data, const signal_graph::Externals &externals) {
              auto &data = *(Note_Frequency_Data *) raw_data;
              data.output = externals.get_external<float>(frequency);
            }),
            new signal_graph::Output<float>(),
          },
          [&frequency](void *raw_data, const signal_graph::Externals &externals) {
//            auto &data = *(Note_Frequency_Data *) raw_data;
//            data.output = stroke.get_frequency();
          });
      }
//      class Note_Frequency : public Node {
//      public:
//          Output<float> output;
//
//          Note_Frequency() :
//            output(this), Node(<#initializer#>) {
//
//          }
//
//          virtual ~Note_Frequency() {
//
//          }
//
//          virtual void update(const Stroke &stroke, void *raw_data, const Externals &externals) override {
//            auto &data = *(Note_Frequency_Data *) raw_data;
//            data.output = stroke.get_frequency();
//          }
//      };
    }
  }
}