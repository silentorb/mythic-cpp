#pragma once

#include "dllexport.h"
#include <shading/Shader_Manager.h>
#include "shading/Program.h"

using namespace shading;

namespace scenery {
  MYTHIC_EXPORT Program &create_solid_program(Shader_Manager &shader_manager);
  MYTHIC_EXPORT Program &create_textured_program(Shader_Manager &shader_manager);
}