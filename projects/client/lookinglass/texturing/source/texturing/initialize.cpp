#include "initialize.h"

using namespace shading;

namespace texturing {
  void initialize_texture_shaders(Shader_Manager &shader_manager) {
    static bool initialized = false;
    if (initialized)
      return;

    initialized = true;

    auto &image_vertex = shader_manager.create_shader(Shader_Type::vertex, "texturing/image.vertex");

    shader_manager.create_program("image",
                                  image_vertex,
                                  shader_manager.create_shader(Shader_Type::fragment, "texturing/image.fragment"));

    shader_manager.create_program("colored-image",
                                  image_vertex,
                                  shader_manager.create_shader(Shader_Type::fragment,
                                                               "texturing/colored-image.fragment"));
  }
}
