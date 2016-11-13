#pragma once

#include "Graph_Generator.h"

namespace signal_graph {

  template <typename Externals>
  class Graph_Instance {
//      const std::vector<Node_Info> node_info;
      std::vector<unsigned char> up_to_date;
      const std::vector<Node_Info<Externals>> & node_info;
      float *output_value;
      Externals &externals;

      // Data was an std:vector but since this is such a cpu intensive
      // class the vector was very slow without compiler optimizations.
      // While this is probably not any faster in release builds, old school allocation is way faster
      // for debug builds without much added complexity.
      char *data;

      void update_node(const Node_Info<Externals> &info);

      bool is_fresh(const Node_Info<Externals> &info) const {
        return up_to_date[info.index];
      }

      void set_fresh(const Node_Info<Externals> &info) {
        up_to_date[info.index] = 1;
      }

      char *get_data(const Node_Info<Externals> &info) const {
        return (char *) data + info.offset;
      }

  public:
      Graph_Instance(const Graph_Generator<Externals> &graph_generator, Externals &externals);
      ~Graph_Instance();
      float update();
  };
}