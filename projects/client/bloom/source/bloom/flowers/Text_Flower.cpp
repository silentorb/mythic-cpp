#include "Text_Flower.h"
#include <typography/Text.h>
#include "drawing/Draw.h"

namespace bloom {

  Text_Flower::Text_Flower(Garden & garden, typography::Font &font, typography::Text_Effect &effect,
                           const string content) :
    Flower(garden),
    text(new typography::Text(font, effect, content)) { }

  Text_Flower::~Text_Flower() { }

  void Text_Flower::set_content(const string &content) {
    text->set_content(content);
  }

  void Text_Flower::set_color(const vec4 value) {
    text->set_color(value);
  }

  void Text_Flower::set_size(float value) {
    text->set_size(value);
  }

  void Text_Flower::render() {
    auto absolute_position = get_absolute_position();
    text->set_position(ivec2((int) absolute_position.x, (int) absolute_position.y));
    text->render();
    Flower::render();
  }

  void Text_Flower::update_dimensions() {
    dimensions = text->get_dimensions();
  }
}