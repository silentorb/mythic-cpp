#include "Property.h"
#include "Node.h"

using namespace std;

namespace signal_graph {

//    void Property::initialize_node(Node &node) {
//      node.add_property(this);
//    }

  void Input_Base::set_other_property(const shared_ptr<Node_Internal> &other_node) {
//    if (other_node.is_empty())
//      return;
    other_property = &static_cast<Output_Base &>(other_node->get_first_output());
    other_node_instance = other_node;
  }

  void Input_Base::set_other_node(const std::shared_ptr<Node_Internal> &other_node) {
    other_node_instance = other_node;
  }

  void Input_Base::attach(const Node &source) {
    if (!source.is_empty())
      source.get_instance()->attach_input(*this, source.get_instance());
  }

}

