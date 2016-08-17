#include "Property.h"
#include "Node.h"

namespace aura {
  namespace graphing {

    void Property::initialize_node(Node &node) {
      node.add_property(*this);
    }

    void Input_Base::set_other_property(Node *other_node) {
      other_property = static_cast<Output_Base*>(&other_node->get_first_output());
    }
  }
}

