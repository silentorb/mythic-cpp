#include "Node.h"

namespace aura {
  namespace graphing {

    void Node::add_property(Property &property) {
      property.offset = data_size;
      properties.push_back(&property);
      data_size += property.get_size();
    }

    Property &Node::get_first_output() const {
      for (auto property: properties) {
        if (property->get_direction() == Property::Direction::output)
          return *property;
      }
      throw runtime_error("Aura node has no output property.");
    }

  }
}