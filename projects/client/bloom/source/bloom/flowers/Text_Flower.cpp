#include "Text_Flower.h"
#include <typography/Text.h>
#include "drawing/Draw.h"

namespace bloom {

  Text_Flower::Text_Flower(Garden &garden, typography::Font &font, typography::Text_Effect &effect,
                           const string content) :
    Flower(garden),
    text(new typography::Text(font, effect, content)) {
    update_dimensions();
  }

  Text_Flower::~Text_Flower() { }

  void Text_Flower::set_content(const string &content) {
    text->set_content(content);
    update_dimensions();
  }

  void Text_Flower::set_color(const vec4 value) {
    text->set_color(value);
  }

  void Text_Flower::set_size(float value) {
    text->set_size(value);
    update_dimensions();
  }

  void Text_Flower::render() {
    Flower::render();
    auto &bounds = get_bounds();
    text->set_position(ivec2((int) bounds.get_position().x, (int) bounds.get_position().y));
    text->render();
  }

  void Text_Flower::update_dimensions() {
    auto text_dimensions = text->get_dimensions();
    dimensions.set_x(Simple_Measurement(text_dimensions.x));
    dimensions.set_y(Simple_Measurement(text_dimensions.y));
  }
}