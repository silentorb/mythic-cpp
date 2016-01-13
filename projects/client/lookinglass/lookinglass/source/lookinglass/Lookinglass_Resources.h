#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "lookinglass/modeling/Mesh_Data.h"
#include "resourceful/Resource_Manager.h"

using namespace std;

namespace lookinglass {
  using namespace modeling;
  namespace shading {
    class Shader_Manager;

    class Shader_Loader;

    class Texture;
  }
  namespace glow {
    class Capabilities;
  }
  class MYTHIC_EXPORT Lookinglass_Resources {

//      unique_ptr<resourceful::Resource_Manager<shading::Program>> program_manager;
//      unique_ptr<resourceful::Resource_Manager> shader_manager;
      unique_ptr<resourceful::Resource_Manager> texture_manager;
      unique_ptr<resourceful::Resource_Manager> mesh_manager;
      unique_ptr<shading::Shader_Manager> shader_manager;
  public:
      Lookinglass_Resources(shading::Shader_Loader *shader_loader, glow::Capabilities &capabilities);

      shading::Shader_Manager &get_shader_manager() const;

      void free();
      void load();

      void add_mesh(Mesh_Data *data) {
        mesh_manager->add_resource(data);
      }

      void add_texture(shading::Texture *texture);
  };
}