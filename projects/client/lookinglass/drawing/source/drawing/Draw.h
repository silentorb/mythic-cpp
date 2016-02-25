#pragma once

#include "dllexport.h"
#include <memory>
#include "glm/glm.hpp"
#include "Group.h"
#include <string>
#include <vector>

namespace lookinglass {
  class Renderable_List;

  class Renderable;

  class House;
}

namespace modeling {
  class Simple_Mesh;

  class Vertex_Schema;
}

namespace shading {
  class Shader_Manager;
}

namespace texturing {
  struct Texture;
}

using namespace std;
using namespace glm;

namespace drawing {
  class Image_Effect;

  class Sprite;

  class Image;

  class Sprite_Layer;

  class MYTHIC_EXPORT Draw : public Group {
      unique_ptr<modeling::Vertex_Schema> solid_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> solid_mesh;

      unique_ptr<modeling::Vertex_Schema> image_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> image_mesh;
      unique_ptr<Image_Effect> default_image_effect;
//      unique_ptr<lookinglass::Renderable_List> sprites;
      lookinglass::House &house;

  public:
      Draw(lookinglass::House &house);
      ~Draw();

      Sprite *create_sprite(Image &image, const glm::vec2 &position = glm::vec2(0, 0));

      void add_sprite_sheet(texturing::Texture &texture, const string &filename);

      Sprite_Layer &create_sprite_layer(texturing::Texture &texture);

      modeling::Simple_Mesh &get_solid_mesh() const {
        return *solid_mesh;
      }

      modeling::Simple_Mesh &get_image_mesh() const {
        return *image_mesh;
      }

      const modeling::Vertex_Schema &get_image_vertex_schema() const {
        return *image_vertex_schema;
      }

//      lookinglass::Renderable &get_renderable() const;

      const ivec2 &get_dimensions() const;

      Image_Effect &get_default_image_effect() const {
        return *default_image_effect;
      }

      lookinglass::House &get_house() const {
        return house;
      }
  };
}



