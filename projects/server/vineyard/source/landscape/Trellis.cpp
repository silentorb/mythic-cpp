#include "Trellis.h"
#include "vineyard/Ground.h"

namespace landscape {

  Trellis::Trellis(const string &name, initializer_list<Property> initializer) :
    name(name) {

    properties.push_back(Property("id", Types::longer));
    int i = 0;
    for (auto &property : initializer) {
      properties.push_back(property);
      properties[i++].set_trellis(*this);
    }

    block_size = 0;
    for (auto &property : properties) {
      property.set_offset(block_size);
      block_size += property.get_info().size;
    }
  }

  void Trellis::finalize(Ground & ground) {
    for (auto &property : properties) {
      if (property.get_type() == Types::reference) {
        property.set_other_trellis(&ground.get_trellis(property.get_name()));
      }
    }
  }
}