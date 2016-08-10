#include "Property.h"
#include "Node.h"

namespace aura {
  namespace graphing {

    void Property::initialize_node(Node &node) {
      node.add_property(*this);
    }

  }
}

