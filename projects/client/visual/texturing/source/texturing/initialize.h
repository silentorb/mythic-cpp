#pragma once

#include "commoner/dllexport.h"
#include "shading/Shader_Manager.h"

namespace texturing {

  MYTHIC_EXPORT void initialize_texture_shaders(shading::Shader_Manager &shader_manager);
}