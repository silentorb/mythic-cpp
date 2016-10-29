#pragma once

#include "aura/graphing/Node.h"
#include <aura/processors/Loop.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      AURA_EXPORT Node Loop_Node(const Node &frequency_source);

//      class AURA_EXPORT Loop_Node : public Node {
//      public:
//          Internal<Loop> loop;
//          Input<float> frequency;
//          Output<float> output;
//
//          Loop_Node(Node *frequency_source);
//          virtual ~Loop_Node();
//
//          virtual void update(const Stroke &stroke, void *raw_data) override {
//            auto &data = *(Oscillator_Data *) raw_data;
//            data.loop.set_frequency(data.frequency);
//            data.output = data.loop.next();
//          }
//      };
    }
  }
}