#pragma once


#include <vector>
#include "Resource.h"
#include <memory>
#include <string>

namespace resourceful {

  class Resource_Handler {
      std::vector<std::weak_ptr<Resource>> resources;

//      void prune();

  public:
      Resource_Handler() {}

      Resource_Handler(const Resource_Handler &) = delete;
      ~Resource_Handler();
      void release();
      void load();
      void add_resource(const std::shared_ptr<Resource> &resource);

//      void remove_resource(Resource *resource);

  };

}

