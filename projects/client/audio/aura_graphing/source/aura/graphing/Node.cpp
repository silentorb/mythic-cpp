#include "Node.h"
#include "nodes/Constant.h"

namespace aura {

  namespace graphing {

    Node::Node(void*) : Node(
      NODE_ID("Empty")
      {}, nullptr) {

    }

    Node Node::create_empty() {
      return Node(nullptr);
    }

#ifdef COMMONER_DEBUG

    Node::Node(const string &name, const initializer_list<Property *> property_initializer, const Node_Update &update) :
      instance(new Node_Instance(name, update)) {
      for (auto property: property_initializer) {
        add_property(property);
      }
      instance->finalize();
    }

#else

    Node::Node(const initializer_list<Property *> property_initializer, const Node_Update &update) :
      instance(new Node_Instance(update)) {
      for (auto property: property_initializer) {
        add_property(property);
      }
      instance->finalize();
    }

#endif

    Node::Node(const Node &node) :
      instance(node.instance) {
      int k = 0;
    }

    Node::Node(float value) : Node(
      NODE_ID("Constant")
      {
        new Constant_Output<float>(value)
      }, nullptr) {
    }

    void Node::add_property(Property *property) {
      instance->properties.push_back(unique_ptr<Property>(property));
      property->node = instance;
    }

    void Node_Instance::finalize() {
      data_size = 0;
      for (auto &property: properties) {
        property->offset = data_size;
        data_size += property->get_size();
      }
    }

    Property &Node_Instance::get_first_output() const {
      for (auto &property: properties) {
        if (property->get_type() == Property::Type::output || property->get_type() == Property::Type::constant)
          return *property;
      }
      throw runtime_error("Aura node has no output property.");
    }

    Input_Base &Node_Instance::get_first_input() const {
      for (auto &property: properties) {
        if (property->get_type() == Property::Type::input)
          return static_cast<Input_Base &>(*property);
      }
      throw runtime_error("Aura node has no output property.");
    }

    Node Node::operator>>(const Node &other) {
      other.get_instance()->get_first_input().set_other_property(*this);
      return other;
    }
  }
}