#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include "Image_Effect.h"
#include "lookinglass/Renderable.h"

using namespace glm;

namespace texturing {
  class Texture;
}

using namespace texturing;

namespace drawing {

  class MYTHIC_EXPORT Sprite : public lookinglass::Renderable {
      vec2 position;
      Texture *texture;
      Image_Effect &effect;

  public:

      Sprite(Image_Effect &effect, Texture &texture, const vec2 &position = vec2(0, 0));

      const vec2 &get_position() const {
        return position;
      }

      void set_position(const vec2 &position) {
        Sprite::position = position;
      }

      void render(lookinglass::Glass &glass);
  };
}