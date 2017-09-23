#include "Graph_Sound.h"
#include <signal_graph/Graph_Instance.h>

namespace foley_graphing {

  template<typename Externals>
  float Graph_Sound<Externals>::update_mono(float delta) {
    sound_data->update(delta);
    return graph_instance->update();
  }

  template<typename Externals>
  bool Graph_Sound<Externals>::is_finished() const {
    return sound_data->is_finished();
  }
}