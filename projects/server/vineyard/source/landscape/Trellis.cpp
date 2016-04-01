#include <vineyard/Seed.h>
#include "Trellis.h"
#include "vineyard/Ground.h"

namespace landscape {

  Trellis::Trellis(const string &name, initializer_list<Property> initializer, Seedery seedery) :
    name(name), seedery(seedery) {

    properties.push_back(Property("id", Types::longer));
    int i = 0;
    for (auto &property : initializer) {
      properties.push_back(property);
      properties[i++].set_trellis(*this);
    }

    offset = sizeof(vineyard::Seed) - sizeof(Identity);
    for (auto &property : properties) {
      property.set_offset(offset);
      offset += property.get_info().size;
    }
  }

  void Trellis::finalize(Ground & ground) {
    for (auto &property : properties) {
      if (property.get_type() == Types::reference || property.get_type() == Types::list) {
        property.set_other_trellis(&ground.get_trellis(property.get_other_trellis_name()));
      }
    }
  }
}