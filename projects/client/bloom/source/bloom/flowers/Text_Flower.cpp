#include "Text_Flower.h"
#include <typography/Text.h>
#include "lookinglass/House.h"
#include "lookinglass/Lookinglass_Resources.h"
#include "bloom/layout/Axis.h"
#include "bloom/Garden.h"
#include "framing/Frame_Info.h"

namespace bloom {

  Text_Flower::Text_Flower(Garden &garden, typography::Font &font, typography::Text_Effect &effect,
                           const string content) :
    Flower_Old(garden),
    text(new typography::Text(font, effect, content)) {
    size = text->get_size();
    set_size(size);
  }

  Text_Flower::Text_Flower(const string content, Flower_Old *parent) :
    Flower_Old(parent) {
    auto &resources = lookinglass::House::get_instance().get_resources();
    text = unique_ptr<typography::Text>(
      new typography::Text(resources.get_font("default"), resources.get_text_effect(), content));
    set_size(text->get_size());
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
    size = value;
    text->set_size(value * garden.get_text_scale() * 800 / garden.get_frame().get_dimensions().y);
    dimensions_changed = true;
  }

  void Text_Flower::set_line_height(float value) {
    text->set_line_height(value);
  }

  void Text_Flower::render() {
    Flower_Old::render();
    text->render();
  }

  void Text_Flower::update_absolute_dimensions(const Axis_Values &parent_values, const vec2 margin) {
    set_size(size); // Update text size in case screen dimensions changed.

    update_axis_cache(parent_values, margin);

//    text->set_max_width(axis_cache.x.length - get_padding() * 2);
    text->set_max_width(axis_cache_inner.x.length * 1.1);
//    auto text_dimensions = text->get_dimensions() + get_padding() * 2;
    auto padding_length_y = axis_cache.y.length - axis_cache_inner.y.length;
    const float font_descender_hack = 1.1;
    auto text_dimensions = text->get_dimensions() + padding_length_y * font_descender_hack;

    auto temp_x = dimensions.get_x();
    auto temp_y = dimensions.get_y();

    if (dimensions.get_x().get_type() == Measurements::stretch)
      dimensions.set_x(Measurement(text_dimensions.x));

//    if (dimensions.get_y().get_type() != Measurements::stretch)
    dimensions.set_y(Measurement(text_dimensions.y));

    update_axis_cache(parent_values, margin);
    dimensions.set_x(temp_x);
    dimensions.set_y(temp_y);

    auto &bounds = get_inner_bounds();
    text->set_position(ivec2((int) bounds.get_position().x, (int) bounds.get_position().y));
  }

}