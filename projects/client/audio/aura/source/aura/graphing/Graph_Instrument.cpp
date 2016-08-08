#include "Graph_Instrument.h"

namespace aura {
  namespace graphing {

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

    void Graph_Instrument::finalize() {
      int total = 0;
      node_info.resize(nodes.size());
      for (int i = 0; i < nodes.size(); ++i) {
        auto &node = nodes[i];
        auto &info = node_info[i];
        info.size = node->get_data_size();
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
      Stroke(note), instrument(instrument), volume_envelope(volume_envelope) {

    }

    float Graph_Stroke::update(float beat_delta) {
      return 0;
    }
  }
}