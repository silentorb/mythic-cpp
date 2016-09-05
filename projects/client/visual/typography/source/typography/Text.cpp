#include "Text.h"
#include "glow.h"
#include "textual/string_additions.h"
#include "typography/Font.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Text_Effect.h"
#include "glow_gl.h"

using namespace textual;

namespace typography {

  const float unit_conversion = 24;

  Text::Text(Font &font, Text_Effect &effect, const string &value) : font(font), effect(effect) {
    set_content(value);
    create_buffers();
    appearance_changed = true;
    needs_recalculating = true;
  }

  Text::~Text() {

  }

  void Text::set_content(const string &value) {
    content = string_replace(value, "\r\n", "\n");
    appearance_changed = true;
    needs_recalculating = true;
  }

  void Text::create_buffers() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glow::set_array_buffer(vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, 4 * sizeof(float), nullptr);
    glow::check_error("creating text buffer");
  }

  void Text::calculate() {
    if (!needs_recalculating)
      return;

    needs_recalculating = false;

    auto without_spaces = string_replace(content, " ", "");
    auto &characters = font.get_characters();
    inserted_newlines.empty();

    element_count = without_spaces.size();
    if (element_count == 0)
      return;

    const float letter_space = 6;
//    const float max_width = _max_width;
    const float max_width = _max_width * unit_conversion / size;
    const float line_step = characters.at('A')->size.y * line_height;
    float x = 0;
    float y = characters.at('A')->size.y;
    bool following_visible_character = false;
    block_dimensions.x = 0;
    int last_space_index = 0;
    float last_space_x = 0;

    for (int i = 0; i < content.size(); ++i) {
      auto c = content[i];
      if (c == ' ') {
//        x += font.get_dimensions().x * 0.8f;
        last_space_x = x;
        last_space_index = i;
        x += font.get_dimensions().x;
        following_visible_character = false;
        continue;
      }

      if (c == '\n') {
        if (x > block_dimensions.x)
          block_dimensions.x = x;

        y += line_step;
        x = 0;
        following_visible_character = false;
        last_space_index = 0;
        last_space_x = 0;
        continue;
      }

      if (following_visible_character) {
        x += letter_space;
      }

      auto& character = characters.at(c);
      float character_width = character->size.x;
      x += character_width;
      if (_max_width && x > max_width && last_space_index > 0) {
        if (last_space_x > block_dimensions.x)
          block_dimensions.x = last_space_x;

        inserted_newlines.push_back(last_space_index);
        y += line_step;
        x -= last_space_x;
        last_space_index = 0;
        last_space_x = 0;
      }

      following_visible_character = true;
    }

    if (x > block_dimensions.x)
      block_dimensions.x = x;

    block_dimensions.y = y;
  }

  void Text::prepare() {
    calculate();

    glBindVertexArray(vao);
    glow::set_array_buffer(vbo);
    auto without_spaces = string_replace(content, " ", "");
    auto &characters = font.get_characters();

    element_count = without_spaces.size();
    if (element_count == 0)
      return;

    auto vertices = new Vertex[6 * element_count];
    float left = 0;
    auto step = 0;
    float top = -characters.at('A')->size.y;
    auto offset = characters.at('A')->size.y * 2;
//    float top = 0;
    //            actual_height = font.characters['A'].size.y * line_size;

    int next_inserted_newline = 0;
    bool following_visible_character = false;

    for (int i = 0; i < content.size(); ++i) {
      auto c = content[i];
      if (next_inserted_newline < inserted_newlines.size() && inserted_newlines[next_inserted_newline] == i) {
        ++next_inserted_newline;
        top += characters.at('A')->size.y * line_height;
        left = 0;
        following_visible_character = false;
        if (c == ' ')
          continue;
      }

      if (c == ' ') {
        left += font.get_dimensions().x * 0.8f;
        following_visible_character = false;
        continue;
      }

      if (c == '\n') {
        top += characters.at('A')->size.y * line_height;
        left = 0;
        following_visible_character = false;
        continue;
      }

      if (following_visible_character)
        left += 6;

      auto &character = characters.at(c);
      float width = character->size.x;
      float height = character->size.y;
      auto x = left;
      float y = top - (character->bearing.y - character->size.y) + offset;//-font.max_height*scale;

      auto texture_width = (float) (character->size.x + 1) / font.get_dimensions().x;

      vertices[step + 5] = Vertex(x, y, 0, character->offset + character->height);
      vertices[step + 4] = Vertex(x, y - height, 0, character->offset);
      vertices[step + 3] = Vertex(x + width, y - height, texture_width, character->offset);
      vertices[step + 2] = Vertex(x + width, y, texture_width, character->offset + character->height);

      vertices[step + 1] = vertices[step + 5];
      vertices[step + 0] = vertices[step + 3];
      step += 6;
      left += character->size.x;
      following_visible_character = true;
    }

//    block_dimensions.x = left;
//    block_dimensions.y = -top;

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * element_count, vertices, GL_DYNAMIC_DRAW);
    glow::set_array_buffer(0);
    delete vertices;
    glow::check_error("Error preparing text.");
    appearance_changed = false;
  }

  void Text::render() {
    if (appearance_changed)
      prepare();

    if (element_count == 0)
      return;

    auto scale = get_scale();
    vec2 scaling = effect.get_viewport().get_unit_scaling();

    auto transform =
      glm::translate(mat4(1), vec3(position.x * scaling.x, position.y * scaling.y, 0))
      * glm::scale(mat4(1), vec3(scale * scaling.x, scale * scaling.y, 1));

//    glUniform2f(glGetUniformLocation(program->get_id(), "scale"), scale, scale);
    effect.activate(color, transform);

    glow::check_error("setting text values");

    font.activate();

    glBindVertexArray(vao);
    glow::check_error("rendering text");

    glDrawArrays(GL_TRIANGLES, 0, 6 * element_count);
    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
    glow::check_error("rendering text");
  }

  vec2 Text::get_dimensions() {
    calculate();
    return block_dimensions * get_scale();
  }

  float Text::get_scale() const {
//    auto &viewport_dimensions = effect.get_viewport_dimensions();
    return size / unit_conversion;

  }
}