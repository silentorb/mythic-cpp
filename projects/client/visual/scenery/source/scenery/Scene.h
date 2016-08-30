#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include <scenery/elements/Group.h>

namespace perspective {
  class Camera;

  struct Viewport_Data;

  class Viewport;
}

namespace through {
  template<typename T>
  class Mist;
};

namespace scenery {

  class MYTHIC_EXPORT Scene : no_copy {
      unique_ptr<perspective::Camera> camera;
      unique_ptr<perspective::Viewport> viewport;
      unique_ptr<scenery::Group> root;

  public:
      Scene(through::Mist<perspective::Viewport_Data> &viewport_mist);
      ~Scene();

      void render();

      perspective::Camera &get_camera() const {
        return *camera;
      }

      perspective::Viewport &get_viewport() const {
        return *viewport;
      }

      scenery::Group &get_root() const {
        return *root;
      }

  };
}



