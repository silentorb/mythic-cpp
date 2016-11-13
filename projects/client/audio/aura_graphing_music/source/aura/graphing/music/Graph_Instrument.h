#pragma once

#include <aura/performance/Performance_Producer.h>
#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "aura/performance/Instrument_Old.h"
#include "signal_graph/Node.h"
#include "signal_graph/Graph_Generator.h"
#include <aura/performance/Musical_Stroke.h>
#include "signal_graph/Graph_Instance.h"

namespace aura {
  namespace graphing {

    template<typename Externals>
    using Externals_Source = std::function<std::unique_ptr<Externals>(const performing::Musical_Stroke &)>;

    template<typename Externals>
    class Graph_Instrument : public performing::Instrument_Old, no_copy {
        const Externals_Source<Externals> externals_source;
        signal_graph::Graph_Generator<Externals> graph_generator;

    public:
        Graph_Instrument(const signal_graph::Node &node, const Externals_Source<Externals> &externals_source);
        virtual ~Graph_Instrument();
        virtual performing::Musical_Stroke *generate_stroke(const sequencing::Note &note) override;

        const signal_graph::Graph_Generator<Externals> &get_graph_generator() const {
          return graph_generator;
        }
    };

    template<typename Externals>
    class Musical_Graph_Stroke : public performing::Musical_Stroke {
        std::unique_ptr<signal_graph::Graph_Instance<Externals>> graph_instance;
        std::unique_ptr<Externals> externals;
//        void update_node(const Node_Info &info);
    public:
        Musical_Graph_Stroke(const sequencing::Note &note, const Graph_Instrument<Externals> &instrument,
                             const Externals_Source<Externals> &externals_source);

        virtual ~Musical_Graph_Stroke() {}

        virtual float update(float beat_delta) override;
    };
  }
}