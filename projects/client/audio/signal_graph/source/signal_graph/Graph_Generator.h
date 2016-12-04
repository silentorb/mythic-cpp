#pragma once

#include "Node.h"

namespace signal_graph {

  template<typename Externals>
  struct Node_Info;

  template<typename Externals>
  struct Input_Info {
      Node_Info<Externals> *node_info;
      Input_Base *property;
  };

  template<typename Externals>
  struct Node_Info {
      int offset;
      int size;
      int index;
      Node_Internal_With_Properties<Externals> *node;
      std::vector<Input_Info<Externals>> inputs;
  };

  template<typename Externals>
  struct Constant_Info {
      float value;
      Input_Info<Externals> input;
  };

  template<typename Externals>
  struct Internal_Info {
      Node_Info<Externals> *node_info;
      Internal_Base *property;
  };

  template<typename Externals>
  class Graph_Generator {
      std::vector<Node> nodes;
      std::vector<Node_Info<Externals>> node_info;
      std::vector<Constant_Info<Externals>> constants;
      std::vector<Internal_Info<Externals>> internal_objects;
      size_t data_byte_size = 0;

      void include_node(const Node &node, int &constant_count, int &internal_objects_count);
      bool contains_node(const Node &node);
      void finalize();
      Node_Info<Externals> *get_node_info(Node_Internal *node);
      void initialize_node_info(Node_Info<Externals> &info, const Node &node, int offset);
      void initialize_input(Input_Base *input_property, Node_Info<Externals> &info, int &input_count);

  public:
      Graph_Generator(const Node &node);
      virtual ~Graph_Generator();
//        virtual Stroke *generate_stroke(const Note &note) override;

      size_t get_data_size() const {
        return data_byte_size;
      }

      const std::vector<Node_Info<Externals>> &get_node_info() const {
        return node_info;
      }

      const std::vector<Constant_Info<Externals>> &get_constants() const {
        return constants;
      }

      const std::vector<Internal_Info<Externals>> &get_internal_objects() const {
        return internal_objects;
      }
  };

}