#pragma once

#include <map>
#include "Entity.h"
#include "Trellis.h"

using namespace std;

namespace metahub {

  class Hub {

      map<Guid, Entity *> entities;
      Trellis *trellis_trellis;
      Trellis *property_trellis;

      void bootstrap_trellises();
      void initialize_entity(Entity *entity, Guid &trellis);
      void free_entity(Entity &entity);
  public:
      Hub();
      ~Hub();

      template<typename T>
      T &create_entity(Guid trellis) {
        auto entity = new T();
        initialize_entity(entity, trellis);
        return *entity;
      }

      Entity &get_entity(const Guid &guid) const {
        return *entities.at(guid);
      }

      Guid &get_property_trellis_id() const {
        return property_trellis->id;
      }

      void delete_entity(Entity &entity);
  };

}

