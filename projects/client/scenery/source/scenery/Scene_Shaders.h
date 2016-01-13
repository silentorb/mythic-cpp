#pragma once

#include <lookinglass/shading/Shader_Manager.h>
#include "lookinglass/shading/Program.h"

using namespace lookinglass:: shading;

namespace scenery {
  Program &create_solid_program(Shader_Manager & shader_manager);
  Program &create_textured_program(Shader_Manager & shader_manager);
}