#pragma once

#include "dllexport.h"
#include "Texture.h"

namespace texturing {

  struct MYTHIC_EXPORT Sprite_Sheet {
      Texture* texture;
      const char *name;
      const int width, height;
  };

  struct MYTHIC_EXPORT Image_Info {
      const Sprite_Sheet * sheet;
      const char *name;
      const int x, y, width, height;
  };
}