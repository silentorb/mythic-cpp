#pragma once

#include <vector>
#include "Property.h"
#include <memory>
#include <commoner/debug-macro.h>

namespace signal_graph {

  typedef std::function<void(void *, const Externals &)> Node_Update;
  typedef std::function<void(void *, const Externals &)> Node_Initializer;
  typedef std::function<void(void *)> Node_Destructor;

  struct Node_Internal : no_copy {
      std::vector<std::unique_ptr<Property>> properties;
      Node_Initializer initializer;
      Node_Destructor destructor;
      Node_Update update;
      size_t data_size = 0;

#ifdef COMMONER_DEBUG
      std::string name;
#endif

      Node_Internal(
#ifdef COMMONER_DEBUG
        const std::string &name,
#endif
        const Node_Initializer &initializer, const Node_Update &update, const Node_Destructor &destructor);

      Node_Internal(
#ifdef COMMONER_DEBUG
        const std::string &name,
#endif
        const Node_Initializer &initializer, const Node_Update &update);

      void initialize_data(void *data, const Externals &externals) {
        if (initializer)
          initializer(data, externals);
      }

      Property &get_first_output() const;
      Input_Base &get_first_input() const;

      std::vector<std::unique_ptr<Property>> &get_properties() {
        return properties;
      }

      const std::vector<std::unique_ptr<Property>> &get_properties() const {
        return properties;
      }

      const Node_Update &get_update() const {
        return update;
      }

      int get_data_size() const {
        return data_size;
      };

//      void add_property(Property *property);
      void set_properties(const std::initializer_list<Property *> property_initializer,
                          std::shared_ptr<Node_Internal> &pointer);

  };

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

      const std::shared_ptr<Node_Internal> &get_instance() const {
        return instance;
      }

      std::vector<std::unique_ptr<Property>> &get_properties() {
        return instance->properties;
      }

      const std::vector<std::unique_ptr<Property>> &get_properties() const {
        return instance->properties;
      }

      Node_Update &get_update() const {
        return instance->update;
      }

      int get_data_size() const {
        return instance->data_size;
      };

      bool is_empty() const {
        return instance->get_properties().size() == 0;
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

    auto internal = std::shared_ptr<Node_Internal>(new Node_Internal(
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