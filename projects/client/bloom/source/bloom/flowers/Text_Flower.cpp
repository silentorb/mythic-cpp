#include "Text_Flower.h"
#include <typography/Text.h>
#include "lookinglass/House.h"
#include "lookinglass/Lookinglass_Resources.h"
#include "bloom/layout/Axis.h"

namespace bloom {

  Text_Flower::Text_Flower(Garden &garden, typography::Font &font, typography::Text_Effect &effect,
                           const string content) :
    Flower(garden),
    text(new typography::Text(font, effect, content)) {
  }

  Text_Flower::Text_Flower(const string content, Flower *parent) :
    Flower(parent) {
    auto &resources = lookinglass::House::get_instance().get_resources();
    text = unique_ptr<typography::Text>(
      new typography::Text(resources.get_font("default"), resources.get_text_effect(), content));
  }

  Text_Flower::~Text_Flower() { }

  void Text_Flower::set_content(const string &content) {
    text->set_content(content);
    dimensions_changed = true;
  }

  void Text_Flower::set_color(const vec4 value) {
    text->set_color(value);
  }

  void Text_Flower::set_size(float value) {
    text->set_size(value);
    dimensions_changed = true;
  }

  void Text_Flower::render() {
    Flower::render();
    auto &bounds = get_bounds();
    float padding = get_padding();

    text->set_position(ivec2((int) bounds.get_position().x + padding, (int) bounds.get_position().y + padding));
    text->render();
  }

  void Text_Flower::update_absolute_dimensions(Axis_Values parent_values, vec2 margin) {
//    set_width(Simple_Measurement(40));
    axis_cache.x = this->calculate_axis<Horizontal_Axis>(parent_values.x, margin.x);
    axis_cache.y = this->calculate_axis<Vertical_Axis>(parent_values.y, margin.y);
//    if (dimensions_changed) {
//      dimensions_changed = false;
      text->set_max_width(axis_cache.x.length - get_padding() * 2);
      auto text_dimensions = text->get_dimensions() + get_padding() * 2;

      auto temp_x = dimensions.get_x_pointer();
      auto temp_y = dimensions.get_y_pointer();
      dimensions.set_x(Simple_Measurement(text_dimensions.x));
      dimensions.set_y(Simple_Measurement(text_dimensions.y));
      axis_cache.x = this->calculate_axis<Horizontal_Axis>(parent_values.x, margin.x);
      axis_cache.y = this->calculate_axis<Vertical_Axis>(parent_values.y, margin.y);
      dimensions.set_x(*temp_x);
      dimensions.set_y(*temp_y);
//    }
  }

//  const Measurement &Text_Flower::get_estimated_width() const {
//    return *estimated_width;
//  }
}