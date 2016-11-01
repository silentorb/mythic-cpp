#include "arithmetic.h"

namespace signal_graph {

  struct Operator_Data {
      float first;
      float second;
      float output;
  };

  template<typename T>
  signal_graph::Node
  Operator(const signal_graph::Node &first, const signal_graph::Node &second, const Node_Update &update) {
    return signal_graph::Node(
      NODE_ID("Operator")
      {
        new signal_graph::Input<T>(first),
        new signal_graph::Input<T>(second),
        new signal_graph::Output<T>(),
      }, update);
  }

  signal_graph::Node Add(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Operator<float>(first, second, [](void *raw_data, const signal_graph::Externals &externals) {
      auto &data = *(Operator_Data *) raw_data;
      data.output = data.first + data.second;
    });
  }

  signal_graph::Node Multiply(const signal_graph::Node &first, const signal_graph::Node &second) {
    return Operator<float>(first, second, [](void *raw_data, const signal_graph::Externals &externals) {
      auto &data = *(Operator_Data *) raw_data;
      data.output = data.first * data.second;
    });
  }
}
