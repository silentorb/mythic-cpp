#include "Mythic_Engine.h"
#include "timing/Quartz.h"
#include "clienting/Client.h"
#include "lookinglass/House.h"
#include "Mythic_Renderer.h"
#include "haft/Input_Manager.h"

namespace mythic {
//  std::map<string, std::unique_ptr<Myth_Info>> myth_registrations;

  Mythic_Engine::Mythic_Engine(Platform_Factory &factory,int width, int height) {

    auto house = new lookinglass::House(factory.create_frame(width, height), factory.create_shader_loader());
    client = new Client(house, factory.create_speaker());

    auto &input_manager = client->get_input_manager();
    auto input_source = factory.create_input_source(input_manager.get_config());
    input_manager.add_input_source(input_source);

    timer = new timing::Quartz();
    renderer = new Mythic_Renderer();
  }

  Mythic_Engine::~Mythic_Engine() {
    delete timer;
    delete client;
  }

//  void Mythic_Engine::add_myth(Myth *myth) {
//    myths[myth->get_name()] = unique_ptr<Myth>(myth);
//  }

  void Mythic_Engine::add_renderable(lookinglass::Renderable &renderable) {
    client->get_house().add_renderable(renderable);
  }

//  void Mythic_Engine::remove_renderable(lookinglass::Renderable &renderable) {
//    client->get_house().remove_renderable(renderable);
//  }

  void Mythic_Engine::update() {
    float delta = timer->update();
    client->update();

    for (auto &myth: myths) {
      myth.second->update(delta);
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

//  void Mythic_Engine::register_myth(Myth_Info *info) {
//    myth_registrations[info->get_name()] = std::unique_ptr<Myth_Info>(info);;
//  }
}