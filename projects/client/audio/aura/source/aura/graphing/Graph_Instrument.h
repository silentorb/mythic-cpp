#pragma once

#include <aura/music/performance/Producer.h>
#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "aura/music/performance/Instrument.h"
#include "Node.h"

namespace aura {
  namespace graphing {

    struct Node_Info {
        int offset;
        int size;
    };

    class AURA_EXPORT Graph_Instrument : public Instrument {
        Producer &producer;
        Note_Envelope_Generator &volume_envelope;
        vector<unique_ptr<Node>> nodes;
        vector<Node_Info> node_info;
        int data_byte_size = 0;

        void include_node(Node *node);
        bool contains_node(Node *node);
        void finalize();

    public:
        Graph_Instrument(Producer &producer, Node *node, Note_Envelope_Generator &volume_envelope);
        virtual ~Graph_Instrument();
        virtual Stroke *generate_stroke(const Note &note) override;
    };

    class Graph_Stroke : public Stroke {
        unique_ptr<Note_Envelope> volume_envelope;
        const Graph_Instrument &instrument;

    public:
        virtual float update(float beat_delta) override;

        Graph_Stroke(const Note &note, const Graph_Instrument &instrument, Note_Envelope *volume_envelope);

        virtual ~Graph_Stroke() {}
    };
  }
}