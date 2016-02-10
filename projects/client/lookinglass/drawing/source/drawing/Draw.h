#pragma once

#include "dllexport.h"
#include <memory>
#include "glm/glm.hpp"
#include <string>
#include <vector>

namespace modeling {
  class Simple_Mesh;

  class Vertex_Schema;
}

namespace shading {
  class Shader_Manager;
}

namespace texturing {
  struct Image_Info;
  struct Sprite_Sheet;
}

using namespace std;

namespace drawing {
  class Image_Effect;

  class Sprite;

  class Sprite_Layer;

  class MYTHIC_EXPORT Draw {
      unique_ptr<modeling::Vertex_Schema> solid_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> solid_mesh;

      unique_ptr<modeling::Vertex_Schema> image_vertex_schema;
      unique_ptr<modeling::Simple_Mesh> image_mesh;
      unique_ptr<Image_Effect> default_image_effect;
      vector<unique_ptr<Sprite>> sprites;

  public:
      Draw(shading::Shader_Manager &shader_manager);
      ~Draw();

      Sprite &create_sprite(const texturing::Image_Info &image, const glm::vec2 &position = glm::vec2(0, 0));

      void add_sprite_sheet(texturing::Sprite_Sheet &sheet, const string &filename);

      Sprite_Layer &create_sprite_layer(texturing::Sprite_Sheet &sheet);

      modeling::Simple_Mesh &get_solid_mesh() const {
        return *solid_mesh;
      }

      modeling::Simple_Mesh &get_image_mesh() const {
        return *image_mesh;
      }
  };
}



