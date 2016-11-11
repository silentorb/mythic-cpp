#include "Node.h"

using namespace std;

namespace signal_graph {

  Node_Internal::Node_Internal(
#ifdef COMMONER_DEBUG
    const std::string &name,
#endif
    const Node_Initializer &initializer, const Node_Update &update, const Node_Destructor &destructor) :
#ifdef COMMONER_DEBUG
    name(name),
#endif
    initializer(initializer), update(update), destructor(destructor) {
  }

  Node_Internal::Node_Internal(
#ifdef COMMONER_DEBUG
    const std::string &name,
#endif
    const Node_Initializer &initializer, const Node_Update &update) :
#ifdef COMMONER_DEBUG
    name(name),
#endif
    initializer(initializer), update(update), destructor(nullptr) {
  }

  Node::Node(void *) : Node(
    NODE_ID("Empty")
    {}, nullptr, nullptr) {

  }

  Node Node::create_empty() {
    return Node(nullptr);
  }

  Node::Node(
#ifdef COMMONER_DEBUG
    const string &name,
#endif
    const initializer_list<Property *> property_initializer,
    const Node_Initializer &initializer, const Node_Update &update) :
    instance(new Node_Internal(
#ifdef COMMONER_DEBUG
      name,
#endif
      initializer, update)) {
    instance->set_properties(property_initializer, instance);
  }

  Node::Node(const Node &node) :
    instance(node.instance) {
    int k = 0;
  }

  Node::Node(float value) : Node(
    NODE_ID("Constant")
    {
      new Constant_Output<float>(value)
    }, nullptr, nullptr) {
  }

  void Node_Internal::set_properties(const std::initializer_list<Property *> property_initializer,
                                     std::shared_ptr<Node_Internal> &pointer) {
    data_size = 0;
    for (auto property: property_initializer) {
      properties.push_back(unique_ptr<Property>(property));
      property->node = pointer;
      property->offset = data_size;
      data_size += property->get_size();
    }
  }

  Property &Node_Internal::get_first_output() const {
    for (auto &property: properties) {
      if (property->get_type() == Property::Type::output || property->get_type() == Property::Type::constant)
        return *property;
    }
    throw runtime_error("Aura node has no output property.");
  }

  Input_Base &Node_Internal::get_first_input() const {
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