#pragma once

#include <aura/graphing/Node.h>
#include <aura/processors/envelopes/ADSR_Envelope.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct ADSR_Node_Data {
          ADSR_Instance instance;
          float output;
      };

      class ADSR_Node : public Node {
      public:
          ADSR settings;
          Internal<ADSR_Instance> instance;
          Output<float> output;

          ADSR_Node(ADSR settings) :
            output(this),
            settings(settings),
            instance(this, [settings](void *data, Producer & producer) {
              new(data) ADSR_Instance(settings);
            }) {

          }

          virtual ~ADSR_Node() {

          }

          virtual void update(const Stroke &stroke, void *raw_data) override {
            auto &data = *(ADSR_Node_Data *) raw_data;
            data.output = update_ADSR(data.instance, stroke.get_progress(), settings);
          }
      };
    }
  }
}