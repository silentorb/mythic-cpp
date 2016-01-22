#include "Text.h"
#include "shading/effects/Color_Effect.h"
#include "lookinglass/glow.h"
#include "textual/string_additions.h"
#include "typography/Font.h"

using namespace textual;
using namespace lookinglass;

namespace typography {

  Text::Text(Font &font, Text_Effect &effect, const string &content) : font(font), effect(effect),
                                                                                 content(content) {
    create_buffers();
    changed = true;
  }

  void Text::create_buffers() {
    uint VAO = vao, VBO = vbo;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    vbo = VBO;
    vao = VAO;

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glow::check_error("creating text buffer");
  }

  void Text::prepare(int viewport_width, int viewport_height) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    auto without_spaces = string_replace(content, " ", "");
    auto &characters = font.get_characters();

    element_count = without_spaces.size();
    if (element_count == 0)
      return;

    auto vertices = new Vertex[6 * element_count];
//		Vertex vertices[60];
    float left = 0;// - viewport_width * 0.5f;
    auto step = 0;
    float top = -characters.at('A')->size.y;
    //            actual_height = font.characters['A'].size.y * line_size;

    auto items = string_replace(content, "\r\n", "\n");
    for (auto &c : items) {
      if (c == ' ') {
        left += font.get_dimensions().x * 0.8f;
        continue;
      }

      if (c == '\n') {
        top += -characters.at('A')->size.y * line_height;
        left = 0;
        continue;
      }

      auto character = characters.at(c);
      float width = character->size.x;
      float height = character->size.y;
      auto x = left;
      float y = top + (character->bearing.y - character->size.y);//-font.max_height*scale;

      //                vertices[step + 0] = new Vertex(x, y, 0, character.offset + height);
      //                vertices[step + 1] = new Vertex(x, y + height, 0, character.offset + character.height);
      //                vertices[step + 2] = new Vertex(x + width, y + height, 0, character.offset + character.height);
      //                vertices[step + 3] = new Vertex(x + width, y, 0, character.offset + height);

      auto texture_width = (float) character->size.x / font.get_dimensions().x;

      vertices[step + 0] = Vertex(x, y, 0, character->offset + character->height);
      vertices[step + 1] = Vertex(x, y + height, 0, character->offset);
      vertices[step + 2] = Vertex(x + width, y + height, texture_width, character->offset);
      vertices[step + 3] = Vertex(x + width, y, texture_width, character->offset + character->height);

//			x = 0;
//			y = -1450;
//			width  = 100;
//			height = 6000;
//			vertices[step + 0] = Vertex(x, y, 0, 1);
//			vertices[step + 1] = Vertex(x, y + height, 0, 0);
//			vertices[step + 2] = Vertex(x + width, y + height, 1, 0);
//			vertices[step + 3] = Vertex(x + width, y, 1, 1);

      vertices[step + 4] = vertices[step + 0];
      vertices[step + 5] = vertices[step + 2];
      step += 6;
      //                left += (character->advance >> 6);
      left += character->size.x + 6;

    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * element_count, vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete vertices;
    glow::check_error("Error preparing text.");
    changed = false;
  }

  void Text::render(Glass &glass) {
    auto dimensions = glass.get_viewport_dimensions();

    if (changed)
      prepare(dimensions.x, dimensions.y);

    if (element_count == 0)
      return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    effect.activate(color, dimensions, position, size * dimensions.x / 18000);

//    float scale = (size * dimensions.x / 36000);
//    float scale = (size * dimensions.x / 18000);
//    glUniform2f(glGetUniformLocation(effect.get_program_id(), "scale"), scale, scale);
    glow::check_error("setting text values");

    glBindTexture(GL_TEXTURE_2D, font.get_texture());
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);
    glow::check_error("rendering text");

    glDrawArrays(GL_TRIANGLES, 0, 6 * element_count);
    glBindVertexArray(0);
    glow::check_error("rendering text");
  }
}