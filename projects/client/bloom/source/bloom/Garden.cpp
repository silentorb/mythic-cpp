#include <bloom/old/Text_Flower.h>
#include "Garden.h"
#include "clienting/Client.h"
#include "haft/Input_State.h"
#include "lookinglass/Lookinglass_Resources.h"
#include <iostream>
#include <bloom/layout/Axis.h>
#include <bloom/flowers/Group.h>
#include "framing/Frame_Info.h"
#include "flowers/Flower.h"

using namespace haft;

namespace bloom {

  Garden *Garden::instance = nullptr;

  Garden::Garden(Draw_Interface &draw) :
    draw(draw),
    select_action(new Action(1, "Select")),
    default_style(new Style()),
    converter(draw.get_frame().get_dimensions()) {
    Measurement::pixel_scale = draw.get_frame().get_pixel_scale();
//    auto simple = Measurement();
//    default_style->set_padding(simple);
    root = unique_ptr<flowers::Group>(new flowers::Group());

    instance = this;
  }

  Garden::~Garden() {}

  void Garden::update_input(haft::Input_State &input_state) {
    auto input_result = garden_input.update_input(input_state);
    flowers::Flower &start = modal_stack.size() > 0
                             ? *modal_stack.top()->root
                             : *root;
    if (input_result.mouse_click) {
      auto &position = input_state.get_position();

//      if (start.check_event(Events::activate_old, vec2(position.x, position.y))) {
//        input_state.clear_gestures();
//      }
      if (start.check_event(Events::activate, vec2(position.x, position.y))) {
        input_state.clear_gestures();
      }
    }

    if (input_result.down) {
      start.check_event(Events::mouse_down, garden_input.get_position());
    }
    else if (input_result.up) {
      start.check_event(Events::mouse_down, garden_input.get_position());
    }
    else if (input_result.dragging) {
      auto &position = garden_input.get_drag_start();

//      if (start.check_event(Events::drag_old, vec2(position.x, position.y))) {
////        input_state.set_handled(*select_action);
//      }

      start.check_event(Events::drag, vec2(position.x, position.y));
    }
  }

  void Garden::update_layout() {
    auto dimensions = draw.get_frame().get_dimensions();
    converter.set_pixel_dimensions(dimensions);

    Axis_Values_Old base_axis_values{
      converter.get_axis_values<Horizontal_Axis>(),
      converter.get_axis_values<Vertical_Axis>()
    };

    auto pixel_dimensions = converter.convert_to_pixels({base_axis_values.x.length, base_axis_values.y.length});
    root->update_dimensions(pixel_dimensions);
    root->update_position(ivec2(), pixel_dimensions);
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

  void Garden::add_modal(flowers::Flower &flower) {
    modal_stack.push(unique_ptr<Modal>(new Modal(&flower)));
  }

  Orientation Garden::get_orientation() const {
    auto &dimensions = get_frame().get_dimensions();
    return dimensions.x > dimensions.y
           ? Orientation::landscape
           : Orientation::portrait;
  }

  flowers::Flower *Garden::get_modal() const {
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

  void Garden::update(float delta) {
    root->update(delta);
  }

}