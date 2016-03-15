#include <bloom/flowers/Text_Flower.h>
#include "Garden.h"
#include "clienting/Client.h"
#include "haft/Input_State.h"
#include "drawing/Draw.h"
#include "lookinglass/House.h"
#include "lookinglass/Lookinglass_Resources.h"
#include <iostream>
#include <bloom/layout/Axis.h>

using namespace haft;

//class Draw_Wrapper : public drawing::Element {
//    Renderable renderable;
//
//public:
//    Draw_Wrapper(const Renderable renderable) : renderable(renderable) { }
//
//    virtual void render() override {
//      renderable();
//    }
//};
int hello2 = 2;

namespace bloom {

  namespace Events {
    const songbird::Song<Flower_Delegate> activate = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> close = songbird::Song<Flower_Delegate>();
    const songbird::Song<Flower_Delegate> cancel = songbird::Song<Flower_Delegate>();
    const int hello = 1;
  };

  Garden *Garden::instance = nullptr;

  Garden::Garden(drawing::Draw &draw) :
    draw(draw),
    select_action(new Action(1, "Select")),
    root(new Flower(*this)),
    converter(draw.get_dimensions()) {
    draw.add_renderable([&]() {
      render();
    });
    instance = this;
    auto &k = Events::hello;
  }

  Garden::~Garden() { }

  void Garden::update_input(haft::Input_State &input_state) {
//    auto &client = engine.get_client();
//    auto &input_state = client.get_current_input_state();
    if (input_state.just_pressed(*select_action)) {
      std::cout << "pressed" << std::endl;
      auto &position = input_state.get_position();

      Flower &start = modal_stack.size() > 0
                      ? *modal_stack.top()->root
                      : *root;

      if (start.check_activate(vec2(position.x, position.y))) {
        input_state.set_handled(*select_action);
      }
    }
  }

  void Garden::render() {
    Axis_Values base_axis_values{
      converter.get_axis_values<Horizontal_Axis>(),
      converter.get_axis_values<Vertical_Axis>()
    };

    root->update_absolute_dimensions(base_axis_values);
    draw.set_depth_test(false);
    root->render();
    draw.set_depth_test(true);
  }

  Text_Flower *Garden::create_text(const string content, const string font) {
    auto &resources = draw.get_house().get_resources();
    return new Text_Flower(*this, resources.get_font(font), resources.get_text_effect(), content);
  }

  Flower &Garden::create_generic_flower() {
    auto flower = new Flower(*this, root);
    return *flower;
  }

  void Garden::add_modal(Flower &flower) {
    modal_stack.push(unique_ptr<Modal>(new Modal(&flower)));
  }

  lookinglass::House &Garden::get_house() const {
    return draw.get_house();
  }

  Orientation Garden::get_orientation() const {
    auto &dimensions = draw.get_dimensions();
    return dimensions.x > dimensions.y
                  ? Orientation::landscape
                  : Orientation::portrait;
  }
}