#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include <string>

namespace shading {
  class Color_Effect;
}
using namespace glm;
using namespace std;

namespace typography {

  class Font;

  class Text {
      unsigned int vao;
      unsigned int vbo;
      Font &font;
      bool changed;
      ivec2 position = ivec2(100, 100);
      float size = 12;
      shading::Color_Effect &effect;
      int element_count;
      float line_height = 1.3;
      string content;

  public:


      Text(Font &font, shading::Color_Effect &effect, const string &content);

      const string &get_content() const {
        return content;
      }

      void set_content(const string &content) {
        Text::content = content;
      }
  };
}