#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include "lookinglass/Renderable.h"

using namespace glm;

namespace shading {
  class Texture;
}

namespace drawing {

  class MYTHIC_EXPORT Sprite: public lookinglass::Renderable {
      vec2 position;
      shading::Texture *texture;

  public:

      Sprite(shading::Texture *texture, const vec2 &position = vec2(0, 0));

      const vec2 &get_position() const {
        return position;
      }

      void set_position(const vec2 &position) {
        Sprite::position = position;
      }


      virtual void render(lookinglass::Glass &glass) override;
  };
}