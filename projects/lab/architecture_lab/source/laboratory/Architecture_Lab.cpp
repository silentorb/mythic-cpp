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
    if(surface){
      surface->assign("swipe_left", *Actions::move_left);
      surface->assign("swipe_right", *Actions::move_right);
      surface->assign("swipe_up", *Actions::move_forward);
      surface->assign("swipe_down", *Actions::move_backward);
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
  }

  void Architecture_Lab::initialize_lookinglass(lookinglass::House &house) {
    auto &shader_manager = house.get_resources().get_shader_manager();
    auto mesh = sculptor::create::box(vec3(10, 10, 10));
    log_info(" loading lab shaders");
    auto &program = shader_manager.create_program("solid",
                                                  *shader_manager.create_shader(Shader_Type::vertex,
                                                                                "scenery/solid.vertex"),
                                                  *shader_manager.create_shader(Shader_Type::fragment,
                                                                                "scenery/solid.fragment"));

    log_info("finished loading lab_shaders");
    auto effect = shared_ptr<Spatial_Effect>(new Spatial_Effect(program));
    auto mesh_data = lookinglass::modeling::mesh_export::output_textured(*mesh);
    auto model = new Model(shared_ptr<Mesh_Data>(mesh_data), effect);
    scene->add(model);
  }

  Architecture_Lab::~Architecture_Lab() {
    engine.remove_renderable(scene);
    delete scene;
    delete camera;
  }

  void Architecture_Lab::update(float delta) {
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