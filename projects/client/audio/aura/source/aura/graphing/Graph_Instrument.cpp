#include "Graph_Instrument.h"

namespace aura {
  namespace graphing {

    size_t get_input_count(const Node *node) {
      size_t result = 0;
      for (auto property: node->get_properties()) {
        if (property->get_type() == Property::Type::input)
          ++result;
      }
      return result;
    }

    Graph_Instrument::Graph_Instrument(Producer &producer, Node *node, Note_Envelope_Generator &volume_envelope) :
      producer(producer), volume_envelope(volume_envelope) {
      int constant_count = 0;
      int internal_objects_count = 0;
      include_node(node, constant_count, internal_objects_count);
      constants.reserve((size_t) constant_count);
      internal_objects.reserve((size_t) internal_objects_count);
      finalize();
    }

    void Graph_Instrument::include_node(Node *node, int &constant_count, int &internal_objects_count) {
      if (contains_node(node))
        return;

      node->finalize();

      nodes.push_back(unique_ptr<Node>(node));

      for (auto property: node->get_properties()) {
        if (property->get_type() == Property::Type::constant) {
          ++constant_count;
        }
        else if (property->get_type() == Property::Type::input) {
          auto other_node = static_cast<Input_Base *>(property)->get_other_node();
          if (other_node) {
            include_node(other_node, constant_count, internal_objects_count);
          }
        }
        else if (property->get_type() == Property::Type::internal) {
          ++internal_objects_count;
        }
      }
    }

    void Graph_Instrument::initialize_input(Input_Base *input_property, Node_Info &info, int &input_count) {
      if (input_property->get_other_property()->get_type() == Property::Type::constant) {
        auto constant = static_cast<Constant_Output_Base *>(input_property->get_other_property());
        Constant_Info constant_info;
        constant_info.input = {
          &info,
          input_property
        };
        constant->assign_constant(&constant_info.value);
        constants.push_back(constant_info);
        delete constant;
      }
      else {
        auto other_node = input_property->get_other_node();
        if (other_node) {
          auto &input = info.inputs[input_count++];
          input.node_info = get_node_info(other_node);
          input.property = input_property;
        }
      }
    }

    void Graph_Instrument::initialize_node_info(Node_Info &info, Node *node, int offset) {
      info.size = node->get_data_size();
      info.offset = offset;
//      info.node = node; // Already done during an earlier pass.
      info.inputs.resize(get_input_count(node));
      int input_count = 0;
      for (auto property: node->get_properties()) {
        if (property->get_type() == Property::Type::input) {
          initialize_input(static_cast <Input_Base *>(property), info, input_count);
        }
        else {
          if (property->get_type() == Property::Type::internal) {
            Internal_Info internal_info;
            internal_info.node_info = &info;
            internal_info.property = static_cast<Internal_Base *>(property);
            internal_objects.push_back(internal_info);
          }
        }
      }
    }

    Node_Info *Graph_Instrument::get_node_info(Node *node) {
      for (int i = 0; i < node_info.size(); ++i) {
        if (node_info[i].node == node)
          return &node_info[i];
      }
      throw runtime_error("Could not find node info from node.");
    }

    void Graph_Instrument::finalize() {
      data_byte_size = 0;
      node_info.resize(nodes.size());
      for (int i = 0; i < nodes.size(); ++i) {
        auto &node = nodes[i];
        auto &info = node_info[i];
        info.node = node.get();
        info.index = i;
      }

      for (int i = 0; i < nodes.size(); ++i) {
        auto &node = nodes[i];
        auto &info = node_info[i];
        initialize_node_info(info, node.get(), data_byte_size);
        data_byte_size += info.size;
      }
    }

    bool Graph_Instrument::contains_node(const Node *node) {
      for (auto &possible: nodes) {
        if (possible.get() == node)
          return true;
      }
      return false;
    }

    Stroke *Graph_Instrument::generate_stroke(const Note &note) {
      return new Graph_Stroke(note, *this, volume_envelope.generate_envelope());
    }

    Graph_Instrument::~Graph_Instrument() {

    }

    Graph_Stroke::Graph_Stroke(const Note &note, const Graph_Instrument &instrument, Note_Envelope *volume_envelope) :
      Stroke(note), node_info(instrument.get_node_info()), volume_envelope(volume_envelope) {
      data.resize(instrument.get_data_size());
      up_to_date.resize(node_info.size());

      // Initialize constants

      // Initialize internal class objects
      for (auto &internal:instrument.get_internal_objects()) {
        internal.property->initialize_data(get_data(*internal.node_info) + internal.property->get_offset());
      }

      // Initialize output_value
      auto root_data = get_data(node_info[0]);
      auto &first_output = node_info[0].node->get_first_output();
      output_value = (float *) (root_data + first_output.get_offset());
    }

    void Graph_Stroke::update_node(const Node_Info &info) {
//      if (is_fresh(info))
//        return;
//
//      set_fresh(info);

      auto data = get_data(info);
//      for (auto &input:info.inputs) {
      for (int i = 0; i < info.inputs.size(); ++i) {
        auto &input = info.inputs[i];
        auto &input_node = *input.node_info;
        update_node(input_node);
        auto a = get_data(input_node);
        auto b = input.property->get_other_property();
        input.property->assign(data, a, *b);
      }
      info.node->update(*this, data);
    }

    float Graph_Stroke::update(float beat_delta) {
      progress += beat_delta;

//      std::fill(up_to_date.begin(), up_to_date.end(), 0);
//			memset(up_to_date.data(), 0, sizeof(bool) * up_to_date.size());

      update_node(node_info[0]);
      float value = *output_value;
      return value * volume_envelope->get_value(progress);
    }
  }
}