#include "Node.h"

using namespace std;

namespace signal_graph {

  Node::Node(void *) {

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
    instance(new Dynamic_Node_Internal(
#ifdef COMMONER_DEBUG
      name,
#endif
      initializer, update)) {
    instance->set_properties(property_initializer, instance);
  }

  Node::Node(const Node &node) :
    instance(node.instance) {
      }

  Node::Node(float value) : Node(
    NODE_ID("Constant")
    {
      new Constant_Output<float>(value)
    }, nullptr, nullptr) {
  }

  Node Node::operator>>(const Node &other) {
//    other.get_instance()->get_first_input().set_other_property(get_instance());
    other.get_instance()->attach_output(get_instance());
    return other;
  }
}