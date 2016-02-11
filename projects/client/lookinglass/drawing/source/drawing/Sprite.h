#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include "Image_Effect.h"
#include "lookinglass/Renderable.h"
#include "Image.h"

using namespace glm;

namespace texturing {
  class Image_Info;
}

using namespace texturing;

namespace drawing {
  class Draw;

  class MYTHIC_EXPORT Sprite : public lookinglass::Renderable {
      vec2 position;
      Image *image;
      Image_Effect *effect;
      Draw &draw;

  public:
      Sprite(Draw &draw, Image_Effect &effect, Image &image, const vec2 &position = vec2(0, 0));
      Sprite(Draw &draw, Image &image, const vec2 &position = vec2(0, 0));

      const vec2 &get_position() const {
        return position;
      }

      void set_position(const vec2 &position) {
        Sprite::position = position;
      }

      void render(lookinglass::Glass &glass);

      const Image &get_image() const {
        return *image;
      }
  };
}