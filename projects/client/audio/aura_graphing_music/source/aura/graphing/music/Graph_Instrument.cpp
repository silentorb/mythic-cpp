#include "Graph_Instrument.h"

namespace aura {
  using namespace performing;

  namespace graphing {

    template<typename Externals>
    Graph_Instrument<Externals>::Graph_Instrument(const signal_graph::Node &node,
                                       const Externals_Source<Externals> &externals_source) :
      graph_generator(node), externals_source(externals_source) {

    }

    template<typename Externals>
    Musical_Stroke *Graph_Instrument<Externals>::generate_stroke(const Note &note) {
      return new Musical_Graph_Stroke<Externals>(note, *this, externals_source);
    }

    template<typename Externals>
    Graph_Instrument<Externals>::~Graph_Instrument() {

    }

    template<typename Externals>
    Musical_Graph_Stroke<Externals>::Musical_Graph_Stroke(const sequencing::Note &note, const Graph_Instrument<Externals> &instrument,
                                               const Externals_Source<Externals> &externals_source) :
      Musical_Stroke(note) {
      externals = externals_source(*this);
      graph_instance = unique_ptr<signal_graph::Graph_Instance<Externals>>(
        new signal_graph::Graph_Instance<Externals>(instrument.get_graph_generator(), *externals));
    }

    template<typename Externals>
    float Musical_Graph_Stroke<Externals>::update(float beat_delta) {
      progress += beat_delta;

//      std::fill(up_to_date.begin(), up_to_date.end(), 0);
//			memset(up_to_date.data(), 0, sizeof(bool) * up_to_date.size());

      return graph_instance->update();
    }
  }
}