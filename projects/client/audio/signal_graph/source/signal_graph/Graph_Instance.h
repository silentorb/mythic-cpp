#pragma once

#include "Graph_Generator.h"
#include "Externals.h"

namespace signal_graph {

  class Graph_Instance {
      const std::vector<Node_Info> node_info;
      std::vector<unsigned char> up_to_date;
      float *output_value;
      const Externals &externals;

      // Data was an std:vector but since this is such a cpu intensive
      // class the vector was very slow without compiler optimizations.
      // While this is probably not any faster in release builds, old school allocation is way faster
      // for debug builds without much added complexity.
      char *data;

      void update_node(const Node_Info &info);

      bool is_fresh(const Node_Info &info) const {
        return up_to_date[info.index];
      }

      void set_fresh(const Node_Info &info) {
        up_to_date[info.index] = 1;
      }

      char *get_data(const Node_Info &info) const {
        return (char *) data + info.offset;
      }

  public:
      Graph_Instance(const Graph_Generator &graph_generator, const Externals &externals);
      ~Graph_Instance();
      float update(float beat_delta);
  };
}