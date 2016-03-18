#pragma once

#include "dllexport.h"

#include <memory>
#include <scenery/Spatial_Effect.h>
#include "Element.h"
#include "glm/glm.hpp"
#include "modeling/Mesh_Data.h"
#include "sculptor/geometry/Mesh.h"

namespace texturing {
  class Texture;
}
using namespace std;
using namespace glm;
using namespace modeling;
using namespace sculptor::geometry;

namespace scenery {

  class MYTHIC_EXPORT Model : public Element {
  private:
      Mesh_Data *mesh_data;
      Spatial_Effect *effect;
      texturing:: Texture*texture = nullptr;
      float opacity = 1;

  public:
      Model(Mesh_Data *mesh_data, Spatial_Effect *effect, Parent *parent = nullptr);
      virtual void render() override;

      float get_opacity() const {
        return opacity;
      }

      void set_opacity(float opacity) {
        Model::opacity = opacity;
      }

      texturing::Texture *get_texture() const {
        return texture;
      }

      void set_texture(texturing::Texture *texture) {
        Model::texture = texture;
      }
  };
}
