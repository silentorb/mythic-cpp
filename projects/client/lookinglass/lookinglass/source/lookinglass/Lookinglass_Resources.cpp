#include "Lookinglass_Resources.h"
#include <lookinglass/glow/Capabilities.h>

using namespace resourceful;

namespace lookinglass {
  using namespace modeling;
  using namespace shading;

  Lookinglass_Resources::Lookinglass_Resources(Shader_Loader *shader_loader, glow::Capabilities &capabilities)
//    :
//    mesh_manager(new Resource_Manager<Mesh_Data>("meshes")) {
  {
    shader_manager = unique_ptr<Shader_Manager>(new Shader_Manager(shader_loader, capabilities));

  }

  shading::Shader_Manager &Lookinglass_Resources::get_shader_manager() const {
    return *shader_manager;
  }
}