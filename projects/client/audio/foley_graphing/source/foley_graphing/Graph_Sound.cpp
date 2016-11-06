#include "Graph_Sound.h"
#include <signal_graph/Graph_Instance.h>

namespace foley_graphing {

  Graph_Sound::Graph_Sound(std::unique_ptr<signal_graph::Graph_Instance> &graph_instance,
                           std::unique_ptr<foley::Sound_Data> &sound_data,
                           std::unique_ptr<signal_graph::Externals> &externals) :
    sound_data(std::move(sound_data)),
    graph_instance(std::move(graph_instance)), externals(std::move(externals)) {}

  float Graph_Sound::update_mono(float delta) {
    sound_data->update(delta);
    return graph_instance->update();
  }
}