#include "Scene_Shaders.h"

namespace scenery {
  Program &create_solid_program(Shader_Manager &shader_manager) {
    return shader_manager.create_program("solid",
                                         shader_manager.create_shader_from_file(Shader_Type::vertex,
                                                                                "scenery/solid.vertex"),
                                         shader_manager.create_shader_from_file(Shader_Type::fragment,
                                                                                "scenery/solid.fragment"),{});
  }

  Program &create_textured_program(Shader_Manager &shader_manager) {
    return shader_manager.create_program("textured",
                                         shader_manager.create_shader_from_file(Shader_Type::vertex,
                                                                                "scenery/textured.vertex"),
                                         shader_manager.create_shader_from_file(Shader_Type::fragment,
                                                                                "scenery/textured.fragment"),{});
  }

  Program &create_colored_program(Shader_Manager &shader_manager) {
    return shader_manager.create_program("colored",
                                         shader_manager.create_shader_from_file(Shader_Type::vertex,
                                                                                "scenery/textured.vertex"),
                                         shader_manager.create_shader_from_file(Shader_Type::fragment,
                                                                                "scenery/textured.fragment"),{});
  }
}