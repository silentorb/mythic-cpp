#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>

using namespace glm;
using namespace std;

namespace drawing {
  class Draw;
}

namespace typography {

  class Font;

  class Text_Effect;

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

  class MYTHIC_EXPORT Text {
      unsigned int vao;
      unsigned int vbo;
      Font &font;
      bool changed;
      ivec2 position = ivec2(0, 100);
      float size = 15;
      Text_Effect &effect;
      int element_count;
      float line_height = 1.4;
      string content;
      vec4 color = vec4(0.9, 0.9, 0.9, 1);
      vec2 block_dimensions;
      float _max_width = 0;
      vector<int> inserted_newlines;

      void create_buffers();
      void calculate();
      void prepare();

  public:

      Text(Font &font, Text_Effect &effect, const string &content);

      const string &get_content() const {
        return content;
      }

      void set_content(const string &value);

      void render();

      void set_color(const vec4 value) {
        color = value;
        changed = true;
      }

      void set_position(const ivec2 &value) {
        if (value != position) {
          position = value;
          changed = true;
        }
      }

      void set_size(float value) {
        size = value;
        changed = true;
      }

      vec2 get_dimensions();

      float get_scale() const;

      float get_max_width() const {
        return _max_width;
      }

      void set_max_width(float max_width) {
        if (this->_max_width == max_width)
          return;

        Text::_max_width = max_width;
        changed = true;
      }
  };
}