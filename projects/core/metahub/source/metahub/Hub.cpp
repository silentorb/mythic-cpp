#include "Hub.h"
#include "Trellis.h"
#include "Property.h"

namespace metahub {

  Hub::Hub() {
    bootstrap_trellises();
  }

  Hub::~Hub() {
    for (auto &entity : entities) {
      free_entity(*entity.second);
      delete entity.second;
    }

    entities.empty();
  }

  void Hub::bootstrap_trellises() {
    trellis_trellis = &create_entity<Trellis>(GUID_EMPTY);
    trellis_trellis->trellis = trellis_trellis->id;
    trellis_trellis->name = new string("Trellis");
    trellis_trellis->properties = new vector<Guid>();

    property_trellis = &create_entity<Trellis>(trellis_trellis->id);
    property_trellis->name = new string("Property");

    auto &name_property = create_entity<Property>(property_trellis->id);
    name_property.name = new string("name");
    name_property.offset = offsetof(struct Property, name);
    name_property.type = Property_Type::String;
    property_trellis->properties->push_back(name_property.id);
  }

  void Hub::initialize_entity(Entity *entity, Guid &trellis) {
    entity->id = create_guid();
    entity->trellis = trellis;
    entity->reference_count = 0;
    entities[entity->id] = entity;
  }

  void Hub::free_entity(Entity &entity) {
    auto &trellis = (Trellis &) get_entity(entity.trellis);
    void *data = &entity;
    for (auto &property_id: *trellis.properties) {
      auto &property = (Property &) get_entity(property_id);
      switch (property.type) {
        case Property_Type::Reference_Array: {
          auto *array = (vector<Guid> *) data + property.offset;
          delete array;
          break;
        }

        case Property_Type::String: {
          auto *array = (string *) data + property.offset;
          delete array;
          break;
        }
      }
    }
  }

  void Hub::delete_entity(Entity &entity) {
    free_entity(entity);
    entities.erase(entity.id);
  }
}