#pragma once

#include "Node.h"

namespace signal_graph {

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
      std::vector<Input_Info> inputs;
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
      std::vector<Node> nodes;
      std::vector<Node_Info> node_info;
      std::vector<Constant_Info> constants;
      std::vector<Internal_Info> internal_objects;
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

      const std::vector<Node_Info> &get_node_info() const {
        return node_info;
      }

      const std::vector<Constant_Info> &get_constants() const {
        return constants;
      }

      const std::vector<Internal_Info> &get_internal_objects() const {
        return internal_objects;
      }
  };

}