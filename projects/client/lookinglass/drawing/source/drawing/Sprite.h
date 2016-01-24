#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include "Image_Effect.h"

using namespace glm;

namespace shading {
  class Texture;
}

namespace drawing {

  class MYTHIC_EXPORT Sprite {
      vec2 position;
      shading::Texture *texture;
      Image_Effect &effect;

  public:

      Sprite(Image_Effect &effect, shading::Texture *texture, const vec2 &position = vec2(0, 0));

      const vec2 &get_position() const {
        return position;
      }

      void set_position(const vec2 &position) {
        Sprite::position = position;
      }


      void render();
  };
}