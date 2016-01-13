#include <scenery/elements/Model.h>
#include <sculptor/create.h>
#include <lookinglass/modeling/mesh_export.h>
#include "Architecture_Lab.h"
#include "scenery/Scene.h"
#include <laboratory/display/Freeform_Camera.h>
#include <lookinglass/shading/Shader_Manager.h>
#include "logger.h"
#include "haft/Input_Manager.h"
#include "Actions.h"
#include "lookinglass/Lookinglass_Resources.h"
#include "lookinglass/glow.h"
#include <stdlib.h>
#include "scenery/Scene_Shaders.h"

using namespace scenery::elements;

namespace laboratory {

  void initialize_input(Input_Configuration &input_config) {
    auto gamepad = input_config.get_device("gamepad");
    if (gamepad) {
      gamepad->assign("LS_Left", *Actions::move_left);
      gamepad->assign("LS_Right", *Actions::move_right);
      gamepad->assign("LS_Up", *Actions::move_forward);
      gamepad->assign("LS_Down", *Actions::move_backward);

      gamepad->assign("LTrigger", *Actions::jump);
      gamepad->assign("RTrigger", *Actions::duck);

      gamepad->assign("RS_Left", *Actions::look_left);
      gamepad->assign("RS_Right", *Actions::look_right);
      gamepad->assign("RS_Up", *Actions::look_up);
      gamepad->assign("RS_Down", *Actions::look_down);

      gamepad->assign("Back", *Actions::quit);
    }

    auto surface = input_config.get_device("surface");
    if (surface) {
//      surface->assign("swipe_left", *Actions::move_left);
//      surface->assign("swipe_right", *Actions::move_right);
//      surface->assign("swipe_up", *Actions::jump);
//      surface->assign("swipe_down", *Actions::duck);
//      surface->assign("swipe_left", *Actions::move_right);
//      surface->assign("swipe_right", *Actions::move_left);
//      surface->assign("swipe_up", *Actions::duck);
//      surface->assign("swipe_down", *Actions::jump);
      surface->assign("swipe_left", *Actions::look_right);
      surface->assign("swipe_right", *Actions::look_left);
      surface->assign("swipe_up", *Actions::look_down);
      surface->assign("swipe_down", *Actions::look_up);
    }
  }

  Architecture_Lab::Architecture_Lab(Mythic_Engine &engine) :
    engine(engine) {
    scene = new Scene();
    engine.add_renderable(scene);
    auto &client = engine.get_client();
    camera = new Freeform_Camera(client.get_house().get_base_viewport());

    auto &input_manager = client.get_input_manager();
    auto &input_config = input_manager.get_config();
//    auto &quit_action = input_config.add_action("quit");
    Actions::initialize(input_config);
    initialize_input(input_config);
    initialize_lookinglass(client.get_house());

//    client.free();
//    client.load();
  }

  float random_in_range(float range) {
    return (((float) rand() / RAND_MAX) * range) - range / 2;
  }

  void Architecture_Lab::initialize_lookinglass(lookinglass::House &house) {
    auto &resources = house.get_resources();
    auto &shader_manager = resources.get_shader_manager();
    srand(1);
    auto mesh = sculptor::create::box(vec3(10, 10, 10));
    log_info(" loading lab shaders");

    log_info("finished loading lab_shaders");
    auto effect = shared_ptr<Spatial_Effect>(new Spatial_Effect(scenery::create_solid_program(shader_manager)));
    auto mesh_data = lookinglass::modeling::mesh_export::output_textured(*mesh);
    resources.add_mesh(mesh_data);

    {
      auto model = new Model(shared_ptr<Mesh_Data>(mesh_data), effect);
      model->set_position(vec3(0, 25, 0));
      scene->add(model);
    }

    {
      auto model = new Model(shared_ptr<Mesh_Data>(mesh_data), effect);
      model->set_position(vec3(5, 25, 0));
      scene->add(model);
    }

    const float range = 100;
    for (int i = 0; i < 300; ++i) {
      auto model = new Model(shared_ptr<Mesh_Data>(mesh_data), effect);
      auto position = vec3(
        random_in_range(range),
        random_in_range(range),
        random_in_range(range)
      );
//      log_info("position %f, %f, %f", position.x, position.y, position.z);
      model->set_position(position);
      scene->add(model);
    }
  }

  Architecture_Lab::~Architecture_Lab() {
    engine.remove_renderable(scene);
    delete scene;
    delete camera;
  }

  void Architecture_Lab::update(float delta) {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    auto &client = engine.get_client();
    auto &input_manager = client.get_input_manager();
    auto &state = input_manager.get_current_state();
    auto &quit_action = input_manager.get_config().get_action("quit");
    if (state.get_event(quit_action)) {
      client.close();
    }

    camera->update(delta, client);
  }
}