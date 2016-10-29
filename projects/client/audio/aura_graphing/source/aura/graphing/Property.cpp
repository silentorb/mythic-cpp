#include "Property.h"
#include "Node.h"

namespace aura {
  namespace graphing {

//    void Property::initialize_node(Node &node) {
//      node.add_property(this);
//    }

    void Input_Base::set_other_property(const Node &other_node) {
      if (other_node.is_empty())
        return;

      other_property = static_cast<Output_Base*>(&other_node.get_instance()->get_first_output());
      other_node_instance = other_node.get_instance();
    }
  }
}

