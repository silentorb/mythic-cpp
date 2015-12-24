#pragma once

#include<memory>
#include <scenery/Spatial_Effect.h>
#include "Element.h"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

  namespace scenery {
    namespace elements {
      class Model : Element {
      private:
          Mesh_Data &mesh;
          shared_ptr<Spatial_Effect *> effect;

      public:
          Model(Mesh_Data& mesh, shared_ptr<Spatial_Effect *> effect);
          void render(Glass &glass);
          mat4 *get_transform();
      };
    }
  }
