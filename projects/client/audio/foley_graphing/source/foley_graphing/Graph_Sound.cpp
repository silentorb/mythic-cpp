#include "Graph_Sound.h"
#include <signal_graph/Graph_Instance.h>

namespace foley_graphing {

  Graph_Sound::Graph_Sound(std::unique_ptr<signal_graph::Graph_Instance> &graph_instance,
                           std::unique_ptr<signal_graph::Externals> &externals) :
    graph_instance(std::move(graph_instance)), externals(std::move(externals)) {}

  float Graph_Sound::update_mono(float delta) const {
    return graph_instance->update();
  }
}