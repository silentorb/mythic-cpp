#pragma once

#include "dllexport.h"

#include <memory>
#include "Simple_Element.h"
#include "modeling/Mesh_Data.h"
#include "sculptor/geometry/Mesh.h"

namespace texturing {
  class Texture;
}
namespace scenery {
  class Spatial_Effect;
}
using namespace std;
using namespace glm;
using namespace modeling;
using namespace sculptor::geometry;

namespace scenery {

  class MYTHIC_EXPORT Model : public Simple_Element {
  protected:
      Mesh_Data *mesh_data;
      Spatial_Effect *effect;
      texturing::Texture *texture = nullptr;
      vec4 color = vec4(1);

  public:
      Model(Mesh_Data *mesh_data, Spatial_Effect *effect, Parent *parent = nullptr);

      virtual ~Model() {}

      virtual void render() override;
      void render(Spatial_Source &spatial);

      float &get_opacity() {
        return color.w;
      }

      void set_opacity(float opacity) {
        color.w = opacity;
      }

      void set_color(vec4 value) {
        color = value;
      }

      texturing::Texture *get_texture() const {
        return texture;
      }

      void set_texture(texturing::Texture *texture) {
        Model::texture = texture;
      }

      void set_effect(Spatial_Effect &effect) {
        this->effect = &effect;
      }

      Mesh_Data *get_mesh_data() const {
        return mesh_data;
      }

      Spatial_Effect *get_effect() const {
        return effect;
      }

      const vec4 &get_color() const {
        return color;
      }
  };
}
