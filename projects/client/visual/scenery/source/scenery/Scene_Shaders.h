#pragma once


#include <shading/Shader_Manager.h>
#include "shading/Program.h"

using namespace shading;

namespace scenery {
  Program &create_solid_program(Shader_Manager &shader_manager);
  Program &create_textured_program(Shader_Manager &shader_manager);
}