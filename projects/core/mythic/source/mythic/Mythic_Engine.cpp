#include <lookinglass/Lookinglass_House.h>
#include "Mythic_Engine.h"
#include "timing/Quartz.h"
#include "clienting/Client.h"
#include "lookinglass/House.h"
#include "Mythic_Renderer.h"
#include "haft/Input_Manager.h"
#include "shading/Shader_Processor.h"
#include "resourceful/File_Loader.h"
#include "Platform_Factory.h"

namespace mythic {

//  class Mythic_Shader_Loader : public shading::Shader_Loader {
//      File_Loader file_loader;
//      shading::Shader_Processor shader_processor;
//
//  public:
//      Mythic_Shader_Loader(const File_Loader &file_loader,
//                           shading::Shader_Processor shader_processor) :
//        file_loader(file_loader), shader_processor(
//        shader_processor) { }
//
//      virtual string load(const string source) override {
//        auto code = file_loader("shaders/" + source);
//        return shader_processor(code);
//      }
//
//  };

  Mythic_Engine::Mythic_Engine(Platform_Factory &factory, int width, int height) :
    storage_path(factory.get_storage_path()) {

    auto house = new lookinglass::Lookinglass_House(factory.create_frame(width, height),
                                                    factory.create_file_loader(),
                                                    factory.create_shader_processor()
    );
    client.reset(new Client(house, factory.create_speaker()));

    auto &input_manager = client->get_input_manager();
    auto input_source = factory.create_input_source(input_manager.get_config());
    input_manager.add_input_source(input_source);

    timer.reset(new timing::Quartz());
    renderer.reset(new Mythic_Renderer());
  }

  Mythic_Engine::~Mythic_Engine() {
  }

  void Mythic_Engine::add_renderable(lookinglass::Renderable &renderable) {
    client->get_house().add_renderable(renderable);
  }

  void Mythic_Engine::update() {
    float delta = timer->update();
    client->update();

    for (auto &myth: myths) {
      myth.second->update(delta);
    }

    for (auto &myth: external_myths) {
      myth->update(delta);
    }
  }

  void Mythic_Engine::loop() {
    while (!client->is_closing()) {
      update();
    }
  }

  void Mythic_Engine::add_myth(Myth *myth) {
    myths[myth->get_name()] = unique_ptr<Myth>(myth);
  }

}