#pragma once

#include "dllexport.h"

#include <memory>
#include <scenery/Spatial_Effect.h>
#include "Element.h"
#include "glm/glm.hpp"
#include "modeling/Mesh_Data.h"
#include "sculptor/geometry/Mesh.h"

using namespace std;
using namespace glm;
using namespace modeling;
using namespace sculptor::geometry;

namespace scenery {

  class MYTHIC_EXPORT Model : public Element {
  private:
      Mesh_Data *mesh_data;
      Spatial_Effect *effect;
      mat4 tranform;

  public:
      Model(Mesh_Data *mesh_data, Spatial_Effect *effect);
      void render(Glass &glass);
      mat4 *get_transform();
  };
}
