#pragma once

#include "dllexport.h"
#include <vector>
#include <memory>
#include "lookinglass/modeling/Mesh_Data.h"
#include "resourceful/Resource_Manager.h"
#include "lookinglass/shading/Shader_Manager.h"

//namespace shading {
//  class Shader_Manager;
//
//  class Shader_Loader;
//}

using namespace std;

namespace lookinglass {
  using namespace modeling;

  namespace glow {
    class Capabilities;
  }
  class MYTHIC_EXPORT Lookinglass_Resources {

//      unique_ptr<resourceful::Resource_Manager<shading::Program>> program_manager;
//      unique_ptr<resourceful::Resource_Manager> shader_manager;
//      unique_ptr<resourceful::Resource_Manager> texture_manager;
      unique_ptr<shading::Shader_Manager> shader_manager;
      unique_ptr<resourceful::Resource_Manager> mesh_manager;
  public:
      Lookinglass_Resources(shading::Shader_Loader *shader_loader, glow::Capabilities &capabilities);

      shading::Shader_Manager &get_shader_manager() const;

      void free();
      void load();
  };
}