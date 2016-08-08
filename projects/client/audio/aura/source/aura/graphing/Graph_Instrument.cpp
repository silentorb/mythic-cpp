#include "Graph_Instrument.h"

namespace aura {
  namespace graphing {

    size_t get_input_count(const Node *node) {
      size_t result = 0;
      for (auto property: node->get_properties()) {
        if (property->get_direction() == Property::Direction::input)
          ++result;
      }
      return result;
    }

    Graph_Instrument::Graph_Instrument(Producer &producer, Node *node, Note_Envelope_Generator &volume_envelope) :
      producer(producer), volume_envelope(volume_envelope) {
      include_node(node);
    }

    void Graph_Instrument::include_node(Node *node) {
      if (contains_node(node))
        return;

      nodes.push_back(unique_ptr<Node>(node));

      for (auto property: node->get_properties()) {
        auto other_node = property->get_other_node();
        if (other_node) {
          include_node(other_node);
        }
      }
    }

    void Graph_Instrument::initialize_node_info(Node_Info &info, Node *node, int offset) {
      info.size = node->get_data_size();
      info.offset = offset;
//      info.node = node; // Already done during an earlier pass.
      info.inputs.resize(get_input_count(node));
      int j = 0;
      for (auto property: node->get_properties()) {
        auto other_node = property->get_other_node();
        if (other_node) {
          auto &input = info.inputs[j++];
          input.node_info = get_node_info(other_node);
          input.property = property;
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
      int total = 0;
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
        initialize_node_info(info, node.get(), total);
        total += info.size;
      }
    }

    bool Graph_Instrument::contains_node(Node *node) {
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

      // Initialize output_value
      auto root_data = get_data(node_info[0]);
      auto &first_output = node_info[0].node->get_first_output();
      output_value = (float *) (root_data + first_output.get_offset());
    }

    void Graph_Stroke::update_node(const Node_Info &info) {
      if (is_fresh(info))
        return;

      set_fresh(info);

      auto data = get_data(info);
      for (auto &input:info.inputs) {
        auto &input_node = *input.node_info;
        update_node(input_node);
        input.property->assign(data, get_data(input_node), *input.property->get_other_property());
      }
      info.node->update(*this, data);
    }

    float Graph_Stroke::update(float beat_delta) {
      progress += beat_delta;
      std::fill(up_to_date.begin(), up_to_date.end(), false);

      update_node(node_info[0]);

      return *output_value * volume_envelope->get_value(progress);
    }
  }
}