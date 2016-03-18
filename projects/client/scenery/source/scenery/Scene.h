#pragma once

#include "dllexport.h"
#include <memory>
#include <scenery/elements/Group.h>

namespace perspective {
  class Camera;

  class Viewport;
}
namespace lookinglass {
  class House;
}

using namespace perspective;

namespace scenery {

  class MYTHIC_EXPORT Scene : no_copy {
      unique_ptr<Camera> camera;
      unique_ptr<Viewport> viewport;
      unique_ptr<scenery::Group> root;
      lookinglass::House &house;

  public:
      Scene(lookinglass::House &house);
      ~Scene();

      void render();

      Camera &get_camera() const {
        return *camera;
      }

      Viewport &get_viewport() const {
        return *viewport;
      }

      scenery::Group &get_root() const {
        return *root;
      }

  };
}



