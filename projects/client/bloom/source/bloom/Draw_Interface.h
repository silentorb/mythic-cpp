#pragma once

#include "bloom/bloom_export.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include <string>

namespace typography {
  class Font;

  class Text_Effect;
}

namespace bloom {

  class BLOOM_EXPORT Draw_Interface {
  public:
      virtual const glm::ivec2 get_dimensions() const = 0;
      virtual void draw_square(float left, float top, float width, float height, const glm::vec4 &color,
                               bool solid) = 0;
      virtual typography::Font &get_font(const std::string &name) const = 0;
      virtual typography::Text_Effect &get_text_effect() const = 0;
      virtual void enable_3d(bool value) = 0;
  };
}