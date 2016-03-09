#include "Button.h"
#include "Text_Flower.h"
#include "bloom/Garden.h"

namespace bloom {

  Button::Button(string text_content, Garden &garden, Flower *parent) :
    Flower(garden, parent) {

    text = garden.create_text(text_content);
      text->set_color(vec4(vec3(0), 1));
//    text->set_color(vec4(1, 0, 0, 1));
    text->set_position(Vector2(Measurement(Measurements::stretch), Measurement(Measurements::stretch)));
    add_child(text);

    set_border(vec4(vec3(0.3), 1));
    set_fill(vec4(vec3(0.8), 1));

    set_dimensions(Measurement(400), Measurement(50));
  }

  void Button::set_text(string content) {
    text->set_content(content);
  }
}