#include "Slider.h"
#include <glm/vec3.hpp>
#include <bloom/flowers/List.h>
#include <songbird/Listener.h>
#include <bloom/Garden.h>
#include <bloom/flowers/Box.h>
#include <bloom/flowers/Fill.h>

using namespace glm;

namespace bloom {
  namespace widgetry {

    Slider::Slider() {
      initialize_layout();
      initialize_interaction();
    }

    void Slider::initialize_layout() {
      set_dimensions(Measurements::stretch, 50);
      auto list_layout = new flowers::Box();
      add_child(list_layout);
      const Measurement knob_width = {Measurements::percent_perpendicular, 60};

      const Measurement side_margin = {Measurements::percent_perpendicular, knob_width.get_value() / 2};
      list_layout->set_left(side_margin);
      list_layout->set_right(side_margin);
      auto list = new flowers::List(flowers::Arrangement::right, 0, list_layout);
      left_side = create_side(vec4(vec3(0.5), 1), list);
      left_side->set_width({Measurements::percent, value * 100});
      auto knob_container = new flowers::Box();
      list->add_child(knob_container);
      knob_container->set_dimensions(0, {Measurements::percent, 100});
      knob = new flowers::Box_Group(knob_container);
      knob->set_dimensions(knob_width, {Measurements::percent, 80});
      auto fill = new flowers::Fill(vec4(0, 0, 1, 1));
      fill->debug_id = 12;
      knob->add_child(fill);
      knob->debug_id = 10;

      right_side = create_side(vec4(vec3(0.9), 1), list);
//  add_child(new spacegame::Fill(glm:: vec4(1, 0, 0, 0.5f)));
    }

    void Slider::initialize_interaction() {
      interactive = new flowers::Interactive_Template<2>(&Events::mouse_down, &Events::drag);
      add_child(interactive);
      interactive->on(Events::mouse_down, [this](const Event &event) {
        auto &input = Garden::get_instance().get_input();
        if (flowers::Interactive::point_is_inside(knob, input.get_position())) {
          auto &knob_bounds = knob->get_absolute_bounds();
          knob_offset = input.get_position().x - (knob_bounds.position.x + knob_bounds.dimensions.x / 2);
//      std::cout << "knob_offset " << to_string(knob_offset) << std::endl;
          return;
        }
        else {
          knob_offset = 0;
//      std::cout << "knob_offset " << "  0" << std::endl;
          update_user_input();
        }
      });

      interactive->on(Events::drag, [this](const Event &event) {
        update_user_input();
      });
    }

    void Slider::update_user_input() {
      auto &input = Garden::get_instance().get_input();
      auto relative = input.get_position().x - get_absolute_bounds().position.x - knob_offset;
      auto result = relative / get_absolute_bounds().dimensions.x;
      if (result < 0)
        result = 0;

      if (result > 1)
        result = 1;

//  std::cout << to_string(result) << std::endl;
      set_value(result);
      if (changed_delegate)
        changed_delegate(result);
    }

    flowers::Box_Group *Slider::create_side(vec4 color, flowers::Parent *parent) {
      auto side = new flowers::Box_Group(parent);
      side->set_height({Measurements::percent, 40});
      side->add_child(new flowers::Fill(color));
      return side;
    }

    void Slider::set_value(float new_value) {
      if (new_value > 1)
        new_value = 1;
      else if (new_value < 0)
        new_value = 0;

      if (value == new_value)
        return;

      value = new_value;
//  std::cout << " " << to_string(value) << std::endl;
      left_side->set_width({Measurements::percent, value * 100});
    }
  }
}