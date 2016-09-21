#include "Trellis.h"

namespace vineyard {

  Trellis::Trellis(const string &name, initializer_list<Property> initializer, int initial_offset, Seedery seedery) :
    name(name), seedery(seedery) {

    properties.push_back(Property("id", Types::longer));
    properties[0].set_trellis(*this);

    int i = 1;
    for (auto &property : initializer) {
      properties.push_back(property);
      properties[i++].set_trellis(*this);
    }

//    offset = sizeof(vineyard::Seed) - sizeof(Identity);
    offset = initial_offset;
    for (auto &property : properties) {
      property.set_offset(offset);
      offset += property.get_info().size;
    }
  }

  void Trellis::finalize(const Trellis_Map &library) {
    for (auto &property : properties) {
      if (property.get_type() == Types::reference || property.get_type() == Types::list) {
        property.set_other_trellis(&library(property.get_other_trellis_name()));
      }
    }
  }
}