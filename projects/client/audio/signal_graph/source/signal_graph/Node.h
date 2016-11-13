#pragma once

#include <vector>
#include "Node_Internal.h"
#include <memory>
#include <commoner/debug-macro.h>

namespace signal_graph {

  class Node {
      friend class Property;

      std::shared_ptr<Node_Internal> instance;

  private:
      Node(void *);

  public:

      Node(const Node &node);

      Node(const std::shared_ptr<Node_Internal> &new_instance) : instance(new_instance) {}

      Node(float value);

      std::shared_ptr<Node_Internal> &get_instance() {
        return instance;
      }

      const std::shared_ptr<Node_Internal> &get_instance() const {
        return instance;
      }

      std::vector<std::unique_ptr<Property>> &get_properties() {
        return instance->get_properties();
      }

      const std::vector<std::unique_ptr<Property>> &get_properties() const {
        return instance->get_properties();
      }


      int get_data_size() const {
        return instance->get_data_size();
      };

      bool is_empty() const {
        return instance.get() == nullptr;
      }

      static Node create_empty();

      Node operator>>(const Node &other);
  };

  template<typename Externals, typename Data_Type>
  Node Node_Instance<Externals, Data_Type>::create_node(const std::initializer_list<signal_graph::Property *> &property_initializer) {
    auto internal = std::shared_ptr<Node_Internal>(
      new Template_Node<Externals, Node_Instance<Externals, Data_Type>>(property_initializer));
    return Node(internal);
  }

#ifdef COMMONER_DEBUG
#define NODE_ID(name) name,
#else
#define NODE_ID(name)
#endif

}