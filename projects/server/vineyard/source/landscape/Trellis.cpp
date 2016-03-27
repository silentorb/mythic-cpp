#include "Trellis.h"

namespace landscape {

  Trellis::Trellis(const string &name, initializer_list<Property> initializer) :
    name(name), properties(initializer) {
    for (auto &property : properties) {
      property.set_trellis(*this);
    }
  }
}