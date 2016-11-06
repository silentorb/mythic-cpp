#pragma once

#include <foley/Sound_Performance.h>
#include <memory>
#include <foley/Sound_Data.h>

namespace signal_graph {
  class Graph_Instance;

  class Externals;
}

namespace foley_graphing {

  class Graph_Sound : public foley::Sound_Performance {
      std::unique_ptr<signal_graph::Graph_Instance> graph_instance;
      std::unique_ptr<signal_graph::Externals> externals;
      std::unique_ptr<foley::Sound_Data> sound_data;

  public:
      Graph_Sound(std::unique_ptr<signal_graph::Graph_Instance> &graph_instance, std::unique_ptr<foley::Sound_Data> &sound_data,
                  std::unique_ptr<signal_graph::Externals> &externals);

      virtual float update_mono(float delta) override;
  };
}