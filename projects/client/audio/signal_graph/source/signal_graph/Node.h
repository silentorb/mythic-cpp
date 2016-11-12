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
#ifdef COMMONER_DEBUG
      Node(const std::string &name, const std::initializer_list<Property *> property_initializer,
           const Node_Initializer &initializer, const Node_Update &update);
#else
      Node(const initializer_list<Property *> property_initializer, const Node_Update &update);
#endif
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

  template<typename T>
  Node create_node(
#ifdef COMMONER_DEBUG
    const std::string &name,
#endif
    const std::initializer_list<signal_graph::Property *> &property_initializer,
    const Node_Update &update) {

    auto internal = std::shared_ptr<Node_Internal>(new Dynamic_Node_Internal(
#ifdef COMMONER_DEBUG
      name,
#endif
      [](void *data, const signal_graph::Externals &externals) {
        new(data)T();
      },
      update,
      [](void *raw_data) {
        auto data = (T *) raw_data;
        data->~T();
      }
    ));
    internal->set_properties(property_initializer, internal);
    return Node(internal);
  }


#ifdef COMMONER_DEBUG
#define NODE_ID(name) name,
#else
#define NODE_ID(name)
#endif

}