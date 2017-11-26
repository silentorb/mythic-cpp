#pragma once

#include "commoner/dllexport.h"
#include <vector>
#include <memory>
#include <shading/Shader_Processor.h>
#include "glm/glm.hpp"

using namespace std;

namespace resourceful {
  class Resource_Manager;

  class Resource;
}

namespace typography {
  class Font;

  class Text_Manager;

  class Text_Effect;
}

namespace shading {
  class Shader_Manager;
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


  class Lookinglass_Resources {

      unique_ptr<resourceful::Resource_Manager> texture_manager;
      unique_ptr<resourceful::Resource_Manager> mesh_manager;
      unique_ptr<shading::Shader_Manager> shader_manager;
      unique_ptr<typography::Text_Manager> text_manager;
      unique_ptr<resourceful::Resource_Manager> general;

  public:
      Lookinglass_Resources(function<const string(const string &)> file_loader,
                            shading::Shader_Processor shader_processor, perspective::Viewport &viewport);
      ~Lookinglass_Resources();

      shading::Shader_Manager &get_shader_manager() const;

      void release();
      void load();

      void add_mesh(modeling::Mesh_Data *data);
      void add_mesh(std::unique_ptr<modeling::Mesh_Data> data);


      void add_texture(texturing::Texture *texture);
      void add_font(const string name, const string path);
      typography::Font &get_font(const string name);
      typography::Text_Effect &get_text_effect() const;
      void add_resource(resourceful::Resource *resource);
      void remove_resource(resourceful::Resource *resource);
  };
}