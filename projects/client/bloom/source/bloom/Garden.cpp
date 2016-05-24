#include <bloom/flowers/Text_Flower.h>
#include "Garden.h"
#include "clienting/Client.h"
#include "haft/Input_State.h"
#include "lookinglass/Lookinglass_Resources.h"
#include <iostream>
#include <bloom/layout/Axis.h>

using namespace haft;

namespace bloom {

  namespace Events {
    const songbird::Song<Flower_Delegate> activate = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> close = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> cancel = songbird::Song<Flower_Delegate>();
  };

  Garden *Garden::instance = nullptr;

  Garden::Garden(Draw_Interface &draw) :
    draw(draw),
    select_action(new Action(1, "Select")),
    default_style(new Style()),
    converter(draw.get_dimensions()) {

//    auto simple = Simple_Measurement();
//    default_style->set_padding(simple);
    root = new Flower(*this);

    instance = this;
  }

  Garden::~Garden() { }

  void Garden::update_input(haft::Input_State &input_state) {
    if (input_state.just_pressed(*select_action)) {
      auto &position = input_state.get_position();

      Flower &start = modal_stack.size() > 0
                      ? *modal_stack.top()->root
                      : *root;

      if (start.check_activate(vec2(position.x, position.y))) {
        input_state.set_handled(*select_action);
      }
    }
  }

  void Garden::update_layout() {
    auto dimensions = draw.get_dimensions();
    converter.set_pixel_dimensions(dimensions);

    Axis_Values base_axis_values{
      converter.get_axis_values<Horizontal_Axis>(),
      converter.get_axis_values<Vertical_Axis>()
    };

    root->update_absolute_dimensions(base_axis_values);
  }

  void Garden::render() {
    update_layout();
    root->render();
  }

  Text_Flower *Garden::create_text(const string content, const string font) {
    return new Text_Flower(*this, draw.get_font(font), draw.get_text_effect(), content);
  }

  void Garden::add_modal(Flower &flower) {
    modal_stack.push(unique_ptr<Modal>(new Modal(&flower)));
  }

  Orientation Garden::get_orientation() const {
    auto &dimensions = draw.get_dimensions();
    return dimensions.x > dimensions.y
           ? Orientation::landscape
           : Orientation::portrait;
  }

  Flower *Garden::get_modal() const {
    if (modal_stack.size() == 0)
      return nullptr;

    return modal_stack.top().get()->root;
  }

  void Garden::pop_modal() {
    modal_stack.pop();
  }
}