#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "lookinglass/modeling/Mesh_Data.h"

using namespace std;

namespace resourceful {
  class Resource_Manager;
}

namespace typography {
  class Font;

  class Font_Manager;
}

namespace shading {
  class Shader_Manager;

  class Shader_Loader;

  class Texture;
}

namespace lookinglass {
  using namespace modeling;

  namespace glow {
    class Capabilities;
  }
  class MYTHIC_EXPORT Lookinglass_Resources {

//      unique_ptr<resourceful::Resource_Manager<shading::Program>> program_manager;
//      unique_ptr<resourceful::Resource_Manager> shader_manager;
      unique_ptr<resourceful::Resource_Manager> texture_manager;
      unique_ptr<resourceful::Resource_Manager> mesh_manager;
      unique_ptr<shading::Shader_Manager> shader_manager;
//      unique_ptr<typography::Font_Manager> font_manager;
  public:
      Lookinglass_Resources(shading::Shader_Loader *shader_loader, glow::Capabilities &capabilities);
      ~Lookinglass_Resources();

      shading::Shader_Manager &get_shader_manager() const;

      void free();
      void load();

      void add_mesh(Mesh_Data *data);

      void add_texture(shading::Texture *texture);
      void add_font(const string name, const string path);
  };
}