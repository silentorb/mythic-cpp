#include <lookinglass/Lookinglass_House.h>
#include "Mythic_Engine.h"
#include "timing/Quartz.h"
#include "clienting/Client.h"
#include "haft/Input_Manager.h"
#include <platforming/Platform_Factory.h>

namespace mythic {

  Mythic_Engine::Mythic_Engine(platforming::Platform_Factory &factory, const Graphic_Options &graphic_options) {

    auto house = new lookinglass::Lookinglass_House(factory.create_frame(graphic_options),
                                                    factory.create_file_loader(),
                                                    factory.create_shader_processor(),
                                                    graphic_options
    );
    client.reset(new clienting::Client(house, factory.create_speaker()));

    auto &input_manager = client->get_input_manager();
    auto input_source = factory.create_input_source(input_manager.get_config());
    input_manager.add_input_source(input_source);

    timer.reset(new timing::Quartz());
  }

  Mythic_Engine::~Mythic_Engine() {

  }

  void Mythic_Engine::update() {
    update(timer->update());
  }
    
    void Mythic_Engine::update(float delta) {
        client->update();
        update_delegate(delta);
    }
    
  void Mythic_Engine::loop() {
    while (!client->is_closing()) {
      update();
    }
  }

}