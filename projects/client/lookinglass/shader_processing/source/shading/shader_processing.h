#pragma once

#include "dllexport.h"
#include <functional>
#include <string>
#include <resourceful/File_Loader.h>
#include "shading/Shader_Type.h"

namespace shading {

  MYTHIC_EXPORT const string process_includes(const string &source, Shader_Type type,
                                              resourceful::File_Loader file_loader);

  MYTHIC_EXPORT const string olden(const string &input, Shader_Type type);

}