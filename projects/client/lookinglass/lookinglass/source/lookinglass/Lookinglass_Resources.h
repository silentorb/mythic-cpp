#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "glm/glm.hpp"

using namespace std;

namespace resourceful {
  class Resource_Manager;
}

namespace typography {
  class Font;

  class Text_Manager;

  class Text_Effect;
}

namespace shading {
  class Shader_Manager;

  class Shader_Loader;
}

namespace texturing {
  class Texture;
}

namespace modeling {
  class Mesh_Data;
}
namespace perspective {
  class Viewport;
}
namespace glow {
  class Capabilities;
}

namespace lookinglass {



  class MYTHIC_EXPORT Lookinglass_Resources {

      unique_ptr<resourceful::Resource_Manager> texture_manager;
      unique_ptr<resourceful::Resource_Manager> mesh_manager;
      unique_ptr<shading::Shader_Manager> shader_manager;
      unique_ptr<typography::Text_Manager> text_manager;

  public:
      Lookinglass_Resources(shading::Shader_Loader *shader_loader, perspective::Viewport &viewport);
      ~Lookinglass_Resources();

      shading::Shader_Manager &get_shader_manager() const;

      void free();
      void load();

      void add_mesh(modeling::Mesh_Data *data);

      void add_texture(texturing::Texture *texture);
      void add_font(const string name, const string path);
      typography::Font &get_font(const string name);
      typography::Text_Effect &get_text_effect() const;
  };
}