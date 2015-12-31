#pragma once
#include "dllexport.h"

#include<memory>
#include <scenery/Spatial_Effect.h>
#include "Element.h"
#include "glm/glm.hpp"
#include "lookinglass/modeling/Mesh_Data.h"

using namespace std;
using namespace glm;
using namespace lookinglass::modeling;

  namespace scenery {
    namespace elements {

      class MYTHIC_EXPORT Model : public Element {
      private:
          Mesh_Data &mesh;
          shared_ptr<Spatial_Effect> effect;
          mat4 tranform;

      public:
          Model(Mesh_Data& mesh, shared_ptr<Spatial_Effect> effect);
          void render(Glass &glass);
          mat4 *get_transform();
      };
    }
  }
