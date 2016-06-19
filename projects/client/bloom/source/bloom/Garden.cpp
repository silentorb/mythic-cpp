#include <bloom/flowers/Text_Flower.h>
#include "Garden.h"
#include "clienting/Client.h"
#include "haft/Input_State.h"
#include "lookinglass/Lookinglass_Resources.h"
#include <iostream>
#include <bloom/layout/Axis.h>
#include "framing/Frame_Info.h"

using namespace haft;

namespace bloom {

  Garden *Garden::instance = nullptr;

  Garden::Garden(Draw_Interface &draw) :
    draw(draw),
    select_action(new Action(1, "Select")),
    default_style(new Style()),
    converter(draw.get_frame().get_dimensions()) {

//    auto simple = Measurement();
//    default_style->set_padding(simple);
    root = new Flower_Old(*this);

    instance = this;
  }

  Garden::~Garden() { }

  void Garden::update_input(haft::Input_State &input_state) {
    auto input_result = garden_input.update_input(input_state);
    if (input_result.mouse_click) {
      auto &position = input_state.get_position();

      Flower_Old &start = modal_stack.size() > 0
                      ? *modal_stack.top()->root
                      : *root;

      if (start.check_event(Events::activate_old, vec2(position.x, position.y))) {
//        input_state.set_handled(*select_action);
      }
      start.check_event_new(Events::activate, vec2(position.x, position.y));
    }
    if (input_result.dragging) {
      auto &position = garden_input.get_drag_start();
      Flower_Old &start = modal_stack.size() > 0
                      ? *modal_stack.top()->root
                      : *root;

      if (start.check_event(Events::drag_old, vec2(position.x, position.y))) {
//        input_state.set_handled(*select_action);
      }
    }
  }

  void Garden::update_layout() {
    auto dimensions = draw.get_frame().get_dimensions();
    converter.set_pixel_dimensions(dimensions);

    Axis_Values_Old base_axis_values{
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

  void Garden::add_modal(Flower_Old &flower) {
    modal_stack.push(unique_ptr<Modal>(new Modal(&flower)));
  }

  Orientation Garden::get_orientation() const {
    auto &dimensions = get_frame().get_dimensions();
    return dimensions.x > dimensions.y
           ? Orientation::landscape
           : Orientation::portrait;
  }

  Flower_Old *Garden::get_modal() const {
    if (modal_stack.size() == 0)
      return nullptr;

    return modal_stack.top().get()->root;
  }

  void Garden::pop_modal() {
    modal_stack.pop();
  }

  const framing::Frame_Info &Garden::get_frame() const {
    return draw.get_frame();
  }

}