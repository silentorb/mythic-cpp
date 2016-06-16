#include "Text.h"
#include <typography/Text.h>
#include "lookinglass/House.h"
#include "lookinglass/Lookinglass_Resources.h"
#include "bloom/Garden.h"
#include "framing/Frame_Info.h"

namespace bloom {
  namespace flowers {

    Text::Text(const string content, Parent *parent) : Child(parent) {
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
      auto& garden = Garden::get_instance();
      text->set_size(value * garden.get_text_scale() * 800 / garden.get_frame().get_dimensions().y);
      dimensions_changed = true;
    }

    void Text::set_line_height(float value) {
      text->set_line_height(value);
    }

    void Text::render() {
      text->render();
    }

//    void Text::update_layout(Axis_Measurements & parent_measurements, Axis_Values &parent_bounds) {
//      text->set_position(ivec2((int) parent_bounds.x.near, (int) parent_bounds.y.near));
//    }
  }
}