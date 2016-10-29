#pragma once

#include <aura/performance/Producer.h>
#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "aura/performance/Instrument.h"
#include "aura/graphing/Node.h"
#include <aura/graphing/Graph_Generator.h>

namespace aura {
  namespace graphing {

    class AURA_EXPORT Graph_Instrument : public Instrument, no_copy {
        Producer &producer;
        Graph_Generator graph_generator;

    public:
        Graph_Instrument(Producer &producer, const Node &node);
        virtual ~Graph_Instrument();
        virtual Musical_Stroke *generate_stroke(const Note &note) override;

        const Graph_Generator &get_graph_generator() const {
          return graph_generator;
        }
    };

    class Musical_Graph_Stroke : public Musical_Stroke {
        const vector<Node_Info> node_info;
        vector<unsigned char> up_to_date;
        float *output_value;

        // Data was an std:vector but since this is such a cpu intensive
        // class the vector was very slow without compiler optimizations.
        // While this is probably not any faster in release builds, old school allocation is way faster
        // for debug builds without much added complexity.
        char *data;

        void update_node(const Node_Info &info);

        bool is_fresh(const Node_Info &info) const {
          return up_to_date[info.index];
        }

        void set_fresh(const Node_Info &info) {
          up_to_date[info.index] = 1;
        }

        char *get_data(const Node_Info &info) const {
          return (char *) data + info.offset;
        }

    public:
        Musical_Graph_Stroke(const Note &note, const Graph_Instrument &instrument, Producer &producer);
        virtual ~Musical_Graph_Stroke();
        virtual float update(float beat_delta) override;
    };
  }
}