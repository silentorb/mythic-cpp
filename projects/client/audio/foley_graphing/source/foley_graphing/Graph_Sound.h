#pragma once

#include <foley/Sound_Performance.h>
#include <memory>
#include <foley/Sound_Data.h>

namespace signal_graph {
  template<typename Externals>
  class Graph_Instance;

  class Externals;
}

namespace foley_graphing {

  template<typename Externals>
  class Graph_Sound : public foley::Sound_Performance {
      std::unique_ptr<signal_graph::Graph_Instance<Externals>> graph_instance;
      std::unique_ptr<Externals> externals;
      std::unique_ptr<foley::Sound_Data> sound_data;

  public:
      Graph_Sound(std::unique_ptr<signal_graph::Graph_Instance<Externals>> &graph_instance,
                  std::unique_ptr<foley::Sound_Data> &sound_data,
                  std::unique_ptr<signal_graph::Externals> &externals) :
        sound_data(std::move(sound_data)),
        graph_instance(std::move(graph_instance)), externals(std::move(externals)) {}

      virtual float update_mono(float delta) override;
      virtual bool is_finished() const override;
  };
}