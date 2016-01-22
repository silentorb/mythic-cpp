#include "Trellis.h"
#include "Hub.h"
#include "Property.h"

namespace metahub {

  Guid &trellis_create_property(Hub &hub, Trellis & trellis) {
    auto &name_property = hub.create_entity<Property>(hub.get_property_trellis_id());
    name_property.name = new string("name");
    name_property.offset = offsetof(struct Property, name);
    name_property.type = Property_Type::String;
    trellis.properties->push_back(name_property.id);
  }
}
