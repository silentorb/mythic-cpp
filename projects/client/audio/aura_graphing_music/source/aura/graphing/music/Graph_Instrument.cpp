#include "Graph_Instrument.h"

namespace aura {
  namespace graphing {

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

    Graph_Instrument::Graph_Instrument(Producer &producer, const Node &node) :
      producer(producer), graph_generator(node) {

    }

    Musical_Stroke *Graph_Instrument::generate_stroke(const Note &note) {
      return new Graph_Stroke(note, *this, producer);
    }

    Graph_Instrument::~Graph_Instrument() {

    }

    Musical_Graph_Stroke::Musical_Graph_Stroke(const Note &note, const Graph_Instrument &instrument, Producer &producer) :
      Musical_Stroke(note), node_info(instrument.get_graph_generator().get_node_info()) {
      auto &graph_generator = instrument.get_graph_generator();

      data = new char[graph_generator.get_data_size()];
      up_to_date.resize(node_info.size());

      // Initialize constants

      // Initialize internal class objects
      for (auto &internal:graph_generator.get_internal_objects()) {
        internal.property->initialize_data(
          get_data(*internal.node_info) + internal.property->get_offset(),
          producer, *this);
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

    Musical_Graph_Stroke::~Graph_Stroke() {
      delete data;
    }

    void Musical_Graph_Stroke::update_node(const Node_Info &info) {
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
      info.node->get_update()(*this, node_data);
    }

    float Musical_Graph_Stroke::update(float beat_delta) {
      progress += beat_delta;

//      std::fill(up_to_date.begin(), up_to_date.end(), 0);
//			memset(up_to_date.data(), 0, sizeof(bool) * up_to_date.size());

      update_node(node_info[0]);
      float value = *output_value;
      return value;
    }
  }
}