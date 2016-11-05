#pragma once

#include "foley/Library.h"
#include <vector>

namespace signal_graph {
  class Graph_Generator;
}

namespace foley_graphing {

  class Graph_Library {
      std::vector<std::unique_ptr<signal_graph::Graph_Generator>> instruments;

  public:
//      std::unique_ptr<foley::Sound> get_sound(int id) const;
  };
}