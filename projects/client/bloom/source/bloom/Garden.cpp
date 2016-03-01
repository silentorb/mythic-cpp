#include <bloom/flowers/Text_Flower.h>
#include "Garden.h"
#include "clienting/Client.h"
#include "haft/Input_State.h"
#include "drawing/Draw.h"
#include "lookinglass/House.h"
#include "lookinglass/Lookinglass_Resources.h"

using namespace haft;

namespace bloom {

  Garden::Garden(drawing::Draw &draw) :
    draw(draw), select_action(new Action(1, "Select")), root(new Flower(*this)) {
    draw.add(*root);
  }

  Garden::~Garden() { }

  void Garden::update_input(haft::Input_State &input_state) {
//    auto &client = engine.get_client();
//    auto &input_state = client.get_current_input_state();
    if (input_state.just_pressed(*select_action)) {
      auto &position = input_state.get_position();
      if (root->check_activate(vec2(position.x, position.y))) {
        input_state.remove_event(*select_action);
      }
    }
  }

  void Garden::render() {
    root->render();
  }

  Text_Flower *Garden::create_text(const string font, const string content) {
    auto &resources = draw.get_house().get_resources();
    return new Text_Flower(*this, resources.get_font(font), resources.get_text_effect(), content);
  }

  Flower &Garden::create_generic_flower() {
    auto flower = new Flower(*this, *root);
    return *flower;
  }
}