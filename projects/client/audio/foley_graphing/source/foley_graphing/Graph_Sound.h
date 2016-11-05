#pragma once

#include <foley/Sound.h>
#include <memory>

namespace signal_graph {
  class Graph_Instance;

  class Externals;
}

namespace foley_graphing {

  class Graph_Sound : public foley::Sound {
      float volume = 1;
      std::unique_ptr<signal_graph::Graph_Instance> graph_instance;
      std::unique_ptr<signal_graph::Externals> externals;

  public:
      Graph_Sound(std::unique_ptr<signal_graph::Graph_Instance> &graph_instance,
                  std::unique_ptr<signal_graph::Externals> &externals);

      void set_volume(float value) {
        volume = value;
      }

      float get_volume() const {
        return volume;
      }

      virtual float update_mono(float delta) const override;
  };
}