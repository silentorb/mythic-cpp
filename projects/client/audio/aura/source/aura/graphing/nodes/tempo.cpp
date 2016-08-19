#include <aura/sequencing/Conductor.h>
#include <aura/music/performance/Producer.h>
#include "tempo.h"

namespace aura {
  namespace graphing {
    namespace nodes {

      struct Tempo_Data {
          float output;
      };

      Node Seconds_Tempo(const Producer &producer) {
        return Node(
          NODE_ID("Seconds_Tempo")
          {
            new Output<float>(),
          },
          [& producer](const Stroke &stroke, void *raw_data) {
            auto &data = *(Tempo_Data *) raw_data;
            data.output = producer.get_conductor().get_seconds_tempo();
          });
      }
    }
  }
}