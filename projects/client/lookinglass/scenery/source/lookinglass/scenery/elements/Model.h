#pragma once

#include<memory>
#include <lookinglass/scenery/Spatial_Effect.h>
#include "Element.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

namespace lookinglass {
  namespace scenery {
    namespace elements {
      class Model : Element {
      private:
          unsigned int mesh_id;
          shared_ptr<Spatial_Effect *> effect;

      public:
          Model(unsigned int mesh_id, shared_ptr<Spatial_Effect *> effect);
          void render(Glass &glass);
          mat4 *get_transform();
      };
    }
  }
}