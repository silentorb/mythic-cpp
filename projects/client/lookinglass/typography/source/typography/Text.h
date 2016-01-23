#pragma once

#include "dllexport.h"
#include "glm/glm.hpp"
#include <string>
#include "lookinglass/Renderable.h"
#include "Text_Effect.h"

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

  class MYTHIC_EXPORT Text : public lookinglass::Renderable {
      unsigned int vao;
      unsigned int vbo;
      Font &font;
      bool changed;
      ivec2 position = ivec2(0, 100);
      float size = 12;
      Text_Effect &effect;
      int element_count;
      float line_height = 1.3;
      string content;
      vec4 color;

      void create_buffers();
      void prepare();

  public:

      Text(Font &font, Text_Effect &effect, const string &content);

      const string &get_content() const {
        return content;
      }

      void set_content(const string &content) {
        Text::content = content;
      }

      virtual void render(lookinglass::Glass &glass) override;

      void set_color(const vec4 value) {
        color = value;
      }

      void set_position(const ivec2 &value) {
        position = value;
      }

      void set_size(float value) {
        size = value;
      }
  };
}