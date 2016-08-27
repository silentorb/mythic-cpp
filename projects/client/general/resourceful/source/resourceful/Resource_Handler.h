#pragma once

#include "commoner/dllexport.h"
#include <vector>
#include "Resource.h"
#include <memory>
#include <string>

namespace resourceful {

  class MYTHIC_EXPORT Resource_Handler : no_copy {
      std::vector<std::weak_ptr<Resource>> resources;

//      void prune();

  public:
      Resource_Handler() {}

      ~Resource_Handler();
      void release();
      void load();
      void add_resource(const std::shared_ptr<Resource> &resource);

//      void remove_resource(Resource *resource);

  };

}

