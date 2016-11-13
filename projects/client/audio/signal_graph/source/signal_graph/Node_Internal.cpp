#include "Node_Internal.h"

using namespace std;

namespace signal_graph {
//
//  Dynamic_Node_Internal::Dynamic_Node_Internal(
//#ifdef COMMONER_DEBUG
//    const std::string &name,
//#endif
//    const Node_Initializer &initializer, const Node_Update &update, const Node_Destructor &destructor) :
//#ifdef COMMONER_DEBUG
//    name(name),
//#endif
//    initializer(initializer), updater(update), destructor(destructor) {
//  }
//
//  Dynamic_Node_Internal::Dynamic_Node_Internal(
//#ifdef COMMONER_DEBUG
//    const std::string &name,
//#endif
//    const Node_Initializer &initializer, const Node_Update &update) :
//#ifdef COMMONER_DEBUG
//    name(name),
//#endif
//    initializer(initializer), updater(update), destructor(nullptr) {
//  }

  template <typename Externals>
  void Node_Internal_With_Properties<Externals>::set_properties(const std::initializer_list<Property *> property_initializer) {
    size_t data_size = 0;
    for (auto property: property_initializer) {
      properties.push_back(unique_ptr<Property>(property));
      property->set_node(get_self());
      property->set_offset(data_size);
      data_size += property->get_size();
    }
  }

  Property &Node_Internal::get_first_output() const {
    for (auto &property: get_properties()) {
      if (property->get_type() == Property::Type::output || property->get_type() == Property::Type::constant)
        return *property;
    }
    throw runtime_error("Aura node has no output property.");
  }

  Input_Base &Node_Internal::get_first_input() const {
    for (auto &property: get_properties()) {
      if (property->get_type() == Property::Type::input)
        return static_cast<Input_Base &>(*property);
    }
    throw runtime_error("Aura node has no output property.");
  }
//
//  void Dynamic_Node_Internal::initialize(void *data, const Externals &externals) const {
//    if (initializer)
//      initializer(data, externals);
//  }
//
//  void Dynamic_Node_Internal::update(void *data, const Externals &externals) const {
//    updater(data, externals);
//  }
//
//  void Dynamic_Node_Internal::free(void *data) const {
//    destructor(data);
//  }

  template <typename Externals>
  void Node_Internal_With_Properties<Externals>::attach_input(Input_Base &input, const shared_ptr<Node_Internal> &instance) {
    input.set_other_property(instance);
  }

  template <typename Externals>
  void Node_Internal_With_Properties<Externals>::attach_output(const std::shared_ptr<Node_Internal> &instance) {
    auto &input = get_first_input();
    if (input.get_other_node().get()) {
      input.get_other_node()->attach_output(instance);
    }
    else {
      input.set_other_property(instance);
    }
  }

//  Node_Internal_With_Properties::Node_Internal_With_Properties() {}

  template <typename Externals>
  Node_Internal_With_Properties<Externals>::Node_Internal_With_Properties(
    const std::initializer_list<Property *> property_initializer) {
    set_properties(property_initializer);
  }

  template <typename Externals>
  const shared_ptr<Node_Internal> Node_Internal_With_Properties<Externals>::get_self() const {
    return self.lock();
  }
}