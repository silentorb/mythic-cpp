#include "Node.h"

using namespace std;

namespace signal_graph {

  Node::Node(void *) {

  }

  Node Node::create_empty() {
    return Node(nullptr);
  }

  Node::Node(const Node &node) :
    instance(node.instance) {
      }

//  Node::Node(float value) : Node(
//        {
//      new Constant_Output<float>(value)
//    }, nullptr, nullptr) {
//  }

  Node Node::operator>>(const Node &other) {
//    other.get_instance()->get_first_input().set_other_property(get_instance());
    other.get_instance()->attach_output(get_instance());
    return other;
  }
}