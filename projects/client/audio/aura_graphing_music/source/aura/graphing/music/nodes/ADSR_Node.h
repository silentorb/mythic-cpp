#pragma once

#include "aura/graphing/Node.h"
#include <aura/processors/envelopes/ADSR_Envelope.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct ADSR_Node_Data {
          ADSR_Instance instance;
          float output;
      };

      Node ADSR_Node(ADSR settings) {
        return Node(
          NODE_ID("ADSR")
          {
            new Internal<ADSR_Instance>([settings](void *data, Producer &producer, const Stroke & stroke) {
              new(data) ADSR_Instance(settings);
            }),
							new Output<float>(),
				},
          [settings](const Stroke &stroke, void *raw_data) {
            auto &data = *(ADSR_Node_Data *) raw_data;
            data.output = update_ADSR(data.instance, stroke.get_position(), settings);
          });
      }
    }
  }
}