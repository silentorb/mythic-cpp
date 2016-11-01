#include "Graph_Generator.h"

using namespace std;

namespace signal_graph {


  size_t get_input_count(const Node &node) {
    size_t result = 0;
    for (auto &property: node.get_properties()) {
      if (property->get_type() == Property::Type::input) {
        auto pointer = static_cast <Input_Base *>(property.get());
        auto other_property = pointer->get_other_property();
        if (pointer->get_other_property()->get_type() != Property::Type::constant)
          ++result;
      }
    }
    return result;
  }

  Graph_Generator::Graph_Generator(const Node &node) {
    int constant_count = 0;
    int internal_objects_count = 0;
    include_node(node, constant_count, internal_objects_count);
    constants.reserve((size_t) constant_count);
    internal_objects.reserve((size_t) internal_objects_count);
    finalize();
  }

  void Graph_Generator::include_node(const Node &node, int &constant_count, int &internal_objects_count) {
    if (contains_node(node))
      return;

    nodes.push_back(node);

    for (auto &property: node.get_properties()) {
      if (property->get_type() == Property::Type::constant) {
        ++constant_count;
      }
      else if (property->get_type() == Property::Type::input) {
        auto other_node = static_cast<Input_Base *>(property.get())->get_other_node();
        if (!other_node.expired()) {
          include_node(Node(other_node.lock()), constant_count, internal_objects_count);
        }
      }
      else if (property->get_type() == Property::Type::internal) {
        ++internal_objects_count;
      }
    }
  }

  void Graph_Generator::initialize_input(Input_Base *input_property, Node_Info &info, int &input_count) {
    if (input_property->get_other_property()->get_type() == Property::Type::constant) {
      auto constant = static_cast<const Constant_Output_Base *>(input_property->get_other_property());
      Constant_Info constant_info;
      constant_info.input = {
        &info,
        input_property
      };
      constant->assign_constant(&constant_info.value);
      constants.push_back(constant_info);
//        delete constant;
    }
    else {
      auto &other_node = input_property->get_other_node();
      if (!other_node.expired()) {
        auto &input = info.inputs[input_count++];
        input.node_info = get_node_info(other_node.lock().get());
        input.property = input_property;
      }
    }
  }

  void Graph_Generator::initialize_node_info(Node_Info &info, const Node &node, int offset) {
    info.size = node.get_data_size();
    info.offset = offset;
//      info.node = node; // Already done during an earlier pass.
    info.inputs.resize(get_input_count(node));
    int input_count = 0;
    for (auto &property: node.get_properties()) {
      if (property->get_type() == Property::Type::input) {
        initialize_input(static_cast <Input_Base *>(property.get()), info, input_count);
      }
      else {
        if (property->get_type() == Property::Type::internal) {
          Internal_Info internal_info;
          internal_info.node_info = &info;
          internal_info.property = static_cast<Internal_Base *>(property.get());
          internal_objects.push_back(internal_info);
        }
      }
    }
  }

  Node_Info *Graph_Generator::get_node_info(Node_Instance *node) {
    for (int i = 0; i < node_info.size(); ++i) {
      if (node_info[i].node == node)
        return &node_info[i];
    }
    throw runtime_error("Could not find node info from node.");
  }

  void Graph_Generator::finalize() {
    data_byte_size = 0;
    node_info.resize(nodes.size());
    for (int i = 0; i < nodes.size(); ++i) {
      auto &node = nodes[i];
      auto &info = node_info[i];
      info.node = node.get_instance().get();
      info.index = i;
    }

    for (int i = 0; i < nodes.size(); ++i) {
      auto &node = nodes[i];
      auto &info = node_info[i];
      initialize_node_info(info, node, data_byte_size);
      data_byte_size += info.size;
    }
  }

  bool Graph_Generator::contains_node(const Node &node) {
    for (auto &possible: nodes) {
      if (&possible == &node)
        return true;
    }
    return false;
  }

//    Stroke *Graph_Generator::generate_stroke(const Note &note) {
//      return new Graph_Stroke(note, *this, producer);
//    }

  Graph_Generator::~Graph_Generator() {

  }

}