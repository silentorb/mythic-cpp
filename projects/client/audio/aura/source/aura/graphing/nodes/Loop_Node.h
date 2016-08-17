#pragma once

#include <aura/graphing/Node.h>
#include <aura/processors/Loop.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Oscillator_Data {
          Loop loop;
          float frequency;
          float output;
      };

      class AURA_EXPORT Loop_Node : public Node {
      public:
          Internal<Loop> loop;
          Input<float> frequency;
          Output<float> output;

          Loop_Node(Node *frequency_source);
          virtual ~Loop_Node();

          virtual void update(const Stroke &stroke, void *raw_data) override {
            auto &data = *(Oscillator_Data *) raw_data;
            data.loop.set_frequency(data.frequency);
            data.output = data.loop.next();
          }
      };
    }
  }
}