#pragma once

#include "dllexport.h"
#include <lookinglass/shading/Shader_Manager.h>
#include "lookinglass/shading/Program.h"

using namespace lookinglass::shading;

namespace scenery {
  MYTHIC_EXPORT Program &create_solid_program(Shader_Manager &shader_manager);
  MYTHIC_EXPORT Program &create_textured_program(Shader_Manager &shader_manager);
}