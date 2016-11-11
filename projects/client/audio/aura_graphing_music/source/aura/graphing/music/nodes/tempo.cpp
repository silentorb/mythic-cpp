#include <aura/sequencing/Conductor.h>
#include "tempo.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Tempo_Data {
          float output;
      };

      signal_graph::Node Seconds_Tempo(const sequencing::Conductor &conductor) {
        return signal_graph::Node(
          NODE_ID("Seconds_Tempo")
          {
            new signal_graph::Output<float>(),
          },
          nullptr,
          [& conductor](void *raw_data, const signal_graph::Externals &externals) {
            auto &data = *(Tempo_Data *) raw_data;
            data.output = conductor.get_seconds_tempo();
          });
      }
    }
  }
}