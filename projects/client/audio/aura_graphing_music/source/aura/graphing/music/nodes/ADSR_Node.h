#pragma once

#include "../../../../../../signal_graph/source/signal_graph/Node.h"
#include <aura/processors/envelopes/ADSR_Envelope.h>

namespace aura {
  namespace graphing {
    namespace nodes {

      struct ADSR_Node_Data {
          ADSR_Instance instance;
          float output;
      };

//      Node ADSR_Node(ADSR settings) {
//        return Node(
//          NODE_ID("ADSR")
//          {
//            new Internal<ADSR_Instance>([settings](void *data) {
//              new(data) ADSR_Instance(settings);
//            }),
//            new Output<float>(),
//          },
//          [settings](void *raw_data, const Externals &externals) {
//            auto &data = *(ADSR_Node_Data *) raw_data;
//            data.output = update_ADSR(data.instance, stroke.get_position(), settings);
//          });
//      }
    }
  }
}