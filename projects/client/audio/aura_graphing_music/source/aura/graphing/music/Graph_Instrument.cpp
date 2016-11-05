#include "Graph_Instrument.h"

namespace aura {
  using namespace performing;

  namespace graphing {

//    size_t get_input_count(const signal_graph::Node &node) {
//      size_t result = 0;
//      for (auto &property: node.get_properties()) {
//        if (property->get_type() == signal_graph::Property::Type::input) {
//          auto pointer = static_cast <Input_Base *>(property.get());
//          auto other_property = pointer->get_other_property();
//          if (pointer->get_other_property()->get_type() != Property::Type::constant)
//            ++result;
//        }
//      }
//      return result;
//    }

    Graph_Instrument::Graph_Instrument(const signal_graph::Node &node,
                                       const Externals_Source &externals_source) :
      graph_generator(node), externals_source(externals_source) {

    }

    Musical_Stroke *Graph_Instrument::generate_stroke(const Note &note) {
      return new Musical_Graph_Stroke(note, *this, externals_source);
    }

    Graph_Instrument::~Graph_Instrument() {

    }

    Musical_Graph_Stroke::Musical_Graph_Stroke(const sequencing::Note &note, const Graph_Instrument &instrument,
                                               const Externals_Source &externals_source) :
      Musical_Stroke(note) {
      externals = externals_source(*this);
      graph_instance = unique_ptr<signal_graph::Graph_Instance>(
        new signal_graph::Graph_Instance(instrument.get_graph_generator(), *externals));
    }

    float Musical_Graph_Stroke::update(float beat_delta) {
      progress += beat_delta;

//      std::fill(up_to_date.begin(), up_to_date.end(), 0);
//			memset(up_to_date.data(), 0, sizeof(bool) * up_to_date.size());

      return graph_instance->update();
    }
  }
}