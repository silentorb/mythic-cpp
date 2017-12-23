#pragma once



#include <memory>
#include "Simple_Element.h"
#include "modeling/Mesh_Data.h"
#include "sculptor/geometry/Mesh.h"

namespace texturing {
  class Texture;
}
namespace scenery {
  class Complex_Spatial_Effect;
}
using namespace std;
using namespace glm;
using namespace modeling;
using namespace sculptor_old::geometry;

namespace scenery {

  class Model : public Simple_Element {
  protected:
      Renderable_Mesh_With_Opacity *mesh_data;
      Complex_Spatial_Effect *effect;
      texturing::Texture *texture = nullptr;
      vec4 color = vec4(1);

  public:
      Model(Renderable_Mesh_With_Opacity *mesh_data, Complex_Spatial_Effect *effect);

      virtual ~Model() {}

      virtual void render() override;
      void render(Spatial_Source &spatial_old);

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

      void set_effect(Complex_Spatial_Effect &effect) {
        this->effect = &effect;
      }

      void set_mesh(Renderable_Mesh_With_Opacity *value) {
        mesh_data = value;
      }

      Renderable_Mesh_With_Opacity *get_mesh() const {
        return mesh_data;
      }

      Complex_Spatial_Effect *get_effect() const {
        return effect;
      }

      const vec4 &get_color() const {
        return color;
      }
  };
}
