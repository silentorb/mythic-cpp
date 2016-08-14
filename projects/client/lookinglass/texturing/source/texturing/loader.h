#pragma once

#include "commoner/dllexport.h"

namespace texturing {

  MYTHIC_EXPORT unsigned char *load_png(const char *filename, int &width, int &height);
}