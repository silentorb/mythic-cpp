#include "Node.h"

namespace aura {
  namespace graphing {

    void Node::add_property(Property &property) {
      properties.push_back(&property);
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