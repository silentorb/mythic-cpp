#pragma once
#include "Node.h"

namespace aura {
  namespace graphing {

    struct Node_Info;

    struct Input_Info {
        Node_Info *node_info;
        Input_Base *property;
    };

    struct Node_Info {
        int offset;
        int size;
        int index;
        Node_Instance *node;
        vector<Input_Info> inputs;
    };

    struct Constant_Info {
        float value;
        Input_Info input;
    };

    struct Internal_Info {
        Node_Info *node_info;
        Internal_Base *property;
    };

    class Graph_Generator {
        vector<Node> nodes;
        vector<Node_Info> node_info;
        vector<Constant_Info> constants;
        vector<Internal_Info> internal_objects;
        size_t data_byte_size = 0;

        void include_node(const Node &node, int &constant_count, int &internal_objects_count);
        bool contains_node(const Node &node);
        void finalize();
        Node_Info *get_node_info(Node_Instance *node);
        void initialize_node_info(Node_Info &info, const Node &node, int offset);
        void initialize_input(Input_Base *input_property, Node_Info &info, int &input_count);

    public:
        Graph_Generator(const Node &node);
        virtual ~Graph_Generator();
//        virtual Stroke *generate_stroke(const Note &note) override;

        size_t get_data_size() const {
          return data_byte_size;
        }

        const vector<Node_Info> &get_node_info() const {
          return node_info;
        }

        const vector<Constant_Info> &get_constants() const {
          return constants;
        }

        const vector<Internal_Info> &get_internal_objects() const {
          return internal_objects;
        }
    };

    class Graph_Stroke : public Stroke {
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
        Graph_Stroke(double duration, const Graph_Generator &graph_generator);
        virtual ~Graph_Stroke();
        virtual float update(float beat_delta) override;
    };
  }
}