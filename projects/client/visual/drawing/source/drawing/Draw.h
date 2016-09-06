#pragma once

#include "commoner/dllexport.h"
#include <memory>
#include "glm/glm.hpp"
#include "Square_Effect.h"
#include <string>
#include <vector>
#include <functional>
#include <modeling/Renderable_Mesh.h>

namespace lookinglass {
//  typedef function<void()> Renderable;

  class House;
}

namespace modeling {
  class Simple_Mesh;
}


namespace shading {
  class Shader_Manager;

  class Vertex_Schema;

  class Program;
}

namespace texturing {
  struct Texture;
}
namespace framing {
  class Frame_Info;
}
using namespace std;
using namespace glm;

namespace drawing {
  class Image_Effect;

  class Sprite;

  class Image;

  class Sprite_Layer;

  class MYTHIC_EXPORT Draw : no_copy {
      unique_ptr<shading::Vertex_Schema> solid_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> solid_mesh;
      unique_ptr<shading::Vertex_Schema> image_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> image_mesh;
      unique_ptr<Image_Effect> default_image_effect;
      unique_ptr<Square_Effect> square_effect;
      shading::Program *flat_program;
      lookinglass::House &house;

  public:
      Draw(lookinglass::House &house);
      ~Draw();

      modeling::Simple_Mesh &get_solid_mesh() const {
        return *solid_mesh;
      }

      modeling::Simple_Mesh &get_image_mesh() const {
        return *image_mesh;
      }

      Square_Effect &get_square_effect() const {
        return *square_effect;
      }

      const shading::Vertex_Schema &get_image_vertex_schema() const {
        return *image_vertex_schema;
      }

      const shading::Vertex_Schema &get_solid_vertex_schema() const {
        return *solid_vertex_schema;
      }

      const ivec2 &get_dimensions() const;

      Image_Effect &get_default_image_effect() const {
        return *default_image_effect;
      }

      lookinglass::House &get_house() const {
        return house;
      }

      void draw_square(float left, float top, float width, float height, modeling::Draw_Method draw_method, Square_Effect &effect,
                       modeling::Renderable_Mesh &mesh);

      void draw_pixel_square(const glm::vec2 &position, const glm::vec2 &dimensions, bool solid,
                             Square_Effect &effect, modeling::Renderable_Mesh &mesh);

      void draw_square(float left, float top, float width, float height, const vec4 &color, bool solid);
      void set_depth(bool value);
      const framing::Frame_Info &get_frame() const;
  };
}



