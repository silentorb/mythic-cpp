#pragma once

#include <aura/music/performance/Producer.h>
#include <aura/processors/Oscillator.h>
#include <aura/processors/envelopes/Note_Envelope.h>
#include <aura/processors/envelopes/Note_Envelope_Generator.h>
#include "aura/music/performance/Instrument.h"
#include "Node.h"

namespace aura {
  namespace graphing {

    struct Node_Info;

    struct Input_Info {
        Node_Info *node_info;
        Property *property;
    };

    struct Node_Info {
        int offset;
        int size;
        int index;
        Node *node;
        vector<Input_Info> inputs;
    };

    class AURA_EXPORT Graph_Instrument : public Instrument {
        Producer &producer;
        Note_Envelope_Generator &volume_envelope;
        vector<unique_ptr<Node>> nodes;
        vector<Node_Info> node_info;
        size_t data_byte_size = 0;

        void include_node(Node *node);
        bool contains_node(Node *node);
        void finalize();
        Node_Info *get_node_info(Node *node);
        void initialize_node_info(Node_Info &info, Node *node, int offset);

    public:
        Graph_Instrument(Producer &producer, Node *node, Note_Envelope_Generator &volume_envelope);
        virtual ~Graph_Instrument();
        virtual Stroke *generate_stroke(const Note &note) override;

        size_t get_data_size() const {
          return data_byte_size;
        }

        const vector<Node_Info> &get_node_info() const {
          return node_info;
        }
    };

    class Graph_Stroke : public Stroke {
        unique_ptr<Note_Envelope> volume_envelope;
        const vector<Node_Info> node_info;
        vector<char> data;
        vector<bool> up_to_date;
        float *output_value;

        void update_node(const Node_Info &info);

        bool is_fresh(const Node_Info &info) const {
          return up_to_date[info.index];
        }

        void set_fresh(const Node_Info &info) {
          up_to_date[info.index] = true;
        }

        char *get_data(const Node_Info &info) const {
          return (char *) data.data() + info.offset;
        }

    public:
        virtual float update(float beat_delta) override;

        Graph_Stroke(const Note &note, const Graph_Instrument &instrument, Note_Envelope *volume_envelope);

        virtual ~Graph_Stroke() {}
    };
  }
}