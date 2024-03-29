#include "Graph_Instance.h"

namespace signal_graph {

  template <typename Externals>
  Graph_Instance<Externals>::Graph_Instance(const Graph_Generator<Externals> &graph_generator, Externals &externals) :
    externals(externals), node_info(graph_generator.get_node_info()) {
    auto &node_info = graph_generator.get_node_info();
    data = new char[graph_generator.get_data_size()];
    up_to_date.resize(node_info.size());

    // Initialize constants

    // Initialize internal class objects
    for (auto &info : node_info) {
      info.node->initialize(get_data(info), externals);
    }

    for (auto &constant : graph_generator.get_constants()) {
      auto node_data = data + constant.input.node_info->offset;
      auto field_data = node_data + constant.input.property->get_offset();
      *(float *) field_data = constant.value;
    }

    // Initialize output_value
    auto root_data = get_data(node_info[0]);
    auto &first_output = node_info[0].node->get_first_output();
    output_value = (float *) (root_data + first_output.get_offset());
  }

  template <typename Externals>
  Graph_Instance<Externals>::~Graph_Instance() {
    for (auto &info: node_info) {

    }
    delete data;
  }

  template <typename Externals>
  void Graph_Instance<Externals>::update_node(const Node_Info<Externals> &info) {
    if (is_fresh(info))
      return;

    set_fresh(info);

    auto node_data = data + info.offset;
    for (int i = 0; i < info.inputs.size(); ++i) {
      auto &input = info.inputs[i];
      auto &input_node = *input.node_info;
      update_node(input_node);
      input.property->assign(
        node_data, get_data(input_node),
        *input.property->get_other_property());
    }
    auto instance = static_cast<Node_Instance_Base<Externals>*>(node_data);
    instance->update(externals);
//    info.node->update(node_data, externals);
  }

  template <typename Externals>
  float Graph_Instance<Externals>::update() {

    std::fill(up_to_date.begin(), up_to_date.end(), 0);
//			memset(up_to_date.data(), 0, sizeof(bool) * up_to_date.size());

    update_node(node_info[0]);
    float value = *output_value;
    return value;
  }

//    float Graph_Stroke::update(float beat_delta) {
//      progress += beat_delta;
//      return instance.update(beat_delta);
//    }

}
