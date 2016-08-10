#include "Node.h"
#include "aura/graphing/nodes/Constant.h"

namespace aura {
  namespace graphing {

    void Node::add_property(Property &property) {
      properties.push_back(&property);
    }

    void Node::finalize() {
      data_size = 0;
      for (auto property: properties) {
        property->offset = data_size;
        data_size += property->get_size();
      }
    }

    Property &Node::get_first_output() const {
      for (auto property: properties) {
        if (property->get_type() == Property::Type::output)
          return *property;
      }
      throw runtime_error("Aura node has no output property.");
    }

  }
}