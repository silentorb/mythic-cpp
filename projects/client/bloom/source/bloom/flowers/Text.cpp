#include "Text.h"
#include <typography/Text.h>
#include <bloom/layout/Axis.h>
#include "lookinglass/House.h"
#include "lookinglass/Lookinglass_Resources.h"
#include "bloom/Garden.h"
#include "framing/Frame_Info.h"

namespace bloom {
  namespace flowers {

    Text::Text(const string &content, Parent *parent) : Child(parent) {
      auto &resources = lookinglass::House::get_instance().get_resources();
      text = unique_ptr<typography::Text>(
        new typography::Text(resources.get_font("default"), resources.get_text_effect(), content));
      set_size(text->get_size());
    }

    Text::~Text() {

    }

    void Text::set_content(const string &content) {
      text->set_content(content);
      dimensions_changed = true;
    }

    void Text::set_color(const glm::vec4 value) {
      text->set_color(value);
    }

    void Text::set_size(float value) {
      size = value;
      auto &garden = Garden::get_instance();
      text->set_size(value * garden.get_text_scale() * 800 / garden.get_frame().get_dimensions().y);
      dimensions_changed = true;
    }

    void Text::set_line_height(float value) {
      text->set_line_height(value);
    }

    void Text::render() {
      text->render();
    }

    glm::vec2 Text::update_relative(const Parent_Dimensions &parent_dimensions) {
      const float font_descender_hack = 1.1;
      auto &converter = Garden::get_instance().get_converter();
      auto text_dimensions = converter.convert_to_pixels(text->get_dimensions() + font_descender_hack);
      vec2 result;
      result.y = text_dimensions.y;

      if (parent_dimensions.x.stretches) {
        result.x = text_dimensions.x;
      }
      else {
        auto length = converter.convert_to_units(parent_dimensions.x.length);
        text->set_max_width(length * font_descender_hack);
        result.x = parent_dimensions.x.length;
      }

      return result;
    }

    void Text::update_absolute(const glm::vec2 &parent_position) {
      auto &converter = Garden::get_instance().get_converter();
      auto unit_position = converter.convert_to_units(parent_position);
      text->set_position(ivec2((int) unit_position.x, (int) unit_position.y));
    }

  }
}