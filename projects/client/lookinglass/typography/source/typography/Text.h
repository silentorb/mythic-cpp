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

  struct Vertex {
      float x, y, u, v;

      Vertex() { }

      Vertex(float x, float y, float u, float v) {
        this->x = x;
        this->y = y;
        this->u = u;
        this->v = v;
      }
  };

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

      void create_buffers();
      void prepare(int viewport_width, int viewport_height);

  public:


      Text(Font &font, shading::Color_Effect &effect, const string &content);

      const string &get_content() const {
        return content;
      }

      void set_content(const string &content) {
        Text::content = content;
      }

      void render(int viewport_width, int viewport_height, vec4 color);


  };
}