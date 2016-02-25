#include "Sprite_Lab.h"
#include <shading/Shader_Manager.h>
#include <texturing/Texture_From_File.h>
#include <drawing/Draw.h>
#include "svg/Texture_From_SVG.h"
#include "haft/Input_Manager.h"
#include "Actions.h"
#include "lookinglass/Lookinglass_Resources.h"
#include "lookinglass/glow.h"
#include "typography/Text.h"
#include "clienting/Client.h"
#include "lookinglass/House.h"
#include "texturing/Texture.h"
#include "drawing/Image_Effect.h"
#include "drawing/Sprite.h"

using namespace typography;
using namespace texturing;
using namespace drawing;

namespace laboratory {

  void initialize_input(Input_Configuration &input_config) {
    auto gamepad = input_config.get_device("gamepad");
    if (gamepad) {

      gamepad->assign("Back", *Actions::quit);
    }

    auto surface = input_config.get_device("surface");
    if (surface) {

    }
  }

  Sprite_Lab::Sprite_Lab(Mythic_Engine &engine) :
    engine(engine) {
    auto &client = engine.get_client();

    auto &input_manager = client.get_input_manager();
    auto &input_config = input_manager.get_config();
//    auto &quit_action = input_config.add_action("quit");
    Actions::initialize(input_config);
    initialize_input(input_config);
    initialize_lookinglass(client.get_house());
  }

  void Sprite_Lab::initialize_lookinglass(lookinglass::House &house) {
    auto &resources = house.get_resources();
    auto &shader_manager = resources.get_shader_manager();

    resources.add_font("text", "resources/fonts/main.ttf");

    debug_text = unique_ptr<Text>(
      new Text(resources.get_font("text"), resources.get_text_effect(), "Hello World abcdefghijklmnopqrstuvwxyz"));
//    debug_text = unique_ptr<Text>(new Text(resources.get_font("text"), resources.get_text_effect(), "Hello World QWERTYUIOPLKJHGFDSAZXCVBNM"));
    debug_text->set_color(vec4(0, 1, 0, 1));
    debug_text->set_position(ivec2(100, 50));
//    engine.add_renderable(*debug_text.get());

//		auto draw = new Draw(shader_manager);
//    auto image_effect = new Image_Effect(shader_manager.get_program("image"), draw->get_image_mesh());

//    {
//      auto texture = new Texture(new svg::Texture_From_SVG("resources/images/test-gradient.svg"));
//      auto sprite = new Sprite(*image_effect, *texture, vec2(300, 0));
//      engine.add_renderable(sprite);
//    }
//
//    {
//      auto texture = new Texture(new Texture_From_File("resources/images/deevee2.png"));
//      auto sprite = new Sprite(*image_effect, *texture, vec2(100, 0));
//      engine.add_renderable(sprite);
//    }
  }

  Sprite_Lab::~Sprite_Lab() {
  }

  void Sprite_Lab::update(float delta) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    auto &client = engine.get_client();
    auto &input_manager = client.get_input_manager();
    auto &state = input_manager.get_current_state();
    auto &quit_action = input_manager.get_config().get_action("quit");
    if (state.get_event(quit_action)) {
      client.close();
    }

  }
}