#include "Button.h"
#include "Text_Flower.h"
#include "bloom/Garden.h"

namespace bloom {

  Button::Button(string text_content, Flower *parent) :
    Flower(parent) {

    text = garden.create_text(text_content);
      text->set_color(vec4(vec3(0), 1));
//    text->set_color(vec4(1, 0, 0, 1));
//    text->set_position(Vector2(Measurement(), Measurement()));
    add_child(text);

    set_border(vec4(vec3(0.3), 1));
    set_fill(vec4(vec3(0.8), 1));
		auto t = Simple_Measurement(100);
    set_dimensions(Simple_Measurement(500), Simple_Measurement(60));
  }

  void Button::set_text(string content) {
    text->set_content(content);
  }

  void Button::set_font_size(int size) {
    text->set_size(size);
  }
}