#include "Property.h"
#include "Node.h"

namespace aura {
  namespace graphing {

    Property::Property(Node *parent) : node(*parent) {
      parent->add_property(*this);
    }

    void Output::assign(void *data, void *other_data, Property &other_property) {
      throw runtime_error("Not supported");
    }
  }
}

