#pragma once

#include "dllexport.h"

namespace texturing {

  MYTHIC_EXPORT unsigned char *load_png(const char *filename, int &width, int &height);
}