#include "Graph_Instance.h"

namespace signal_graph {


//    Graph_Instance::Graph_Instance(const Graph_Generator &graph_generator, const Externals &externals) :
//      Stroke(duration), instance(graph_generator) {
//
//    }

  Graph_Instance::Graph_Instance(const Graph_Generator &graph_generator, const Externals &externals) :
    node_info(graph_generator.get_node_info()), externals(externals) {
    data = new char[graph_generator.get_data_size()];
    up_to_date.resize(node_info.size());

    // Initialize constants

    // Initialize internal class objects
    for (auto &internal:graph_generator.get_internal_objects()) {
      internal.property->initialize_data(get_data(*internal.node_info) + internal.property->get_offset(),
                                         externals);
    }

    for (auto &constant: graph_generator.get_constants()) {
      auto node_data = data + constant.input.node_info->offset;
      auto field_data = node_data + constant.input.property->get_offset();
      *(float *) field_data = constant.value;
    }
    // Initialize output_value
    auto root_data = get_data(node_info[0]);
    auto &first_output = node_info[0].node->get_first_output();
    output_value = (float *) (root_data + first_output.get_offset());
  }

  Graph_Instance::~Graph_Instance() {
    delete data;
  }

  void Graph_Instance::update_node(const Node_Info &info) {
//      if (is_fresh(info))
//        return;
//
//      set_fresh(info);

    auto node_data = data + info.offset;
    for (int i = 0; i < info.inputs.size(); ++i) {
      auto &input = info.inputs[i];
      auto &input_node = *input.node_info;
      update_node(input_node);
      input.property->assign(
        node_data, get_data(input_node),
        *input.property->get_other_property());
    }
    info.node->get_update()(node_data, externals);
  }

  float Graph_Instance::update() {

//      std::fill(up_to_date.begin(), up_to_date.end(), 0);
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
