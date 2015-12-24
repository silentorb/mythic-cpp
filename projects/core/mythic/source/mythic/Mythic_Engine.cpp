#include "Mythic_Engine.h"
#include "timing/Quartz.h"
#include "clienting/Client.h"
#include "lookinglass/House.h"
#include "Mythic_Renderer.h"

namespace mythic {
  Mythic_Engine::Mythic_Engine(Client *client)
    : client(client) {
    timer = new timing::Quartz();
    renderer = new Mythic_Renderer();
    auto house = client->get_house();
    house->add_renderable(renderer);
  }

  Mythic_Engine::~Mythic_Engine() {
    delete timer;
  }

  void Mythic_Engine::add_myth(Myth *myth) {
    myths[myth->get_name()] = unique_ptr<Myth>(myth);
  }

  void Mythic_Engine::add_renderable(lookinglass::Renderable *renderable) {
    renderer->add_renderable(renderable);
  }

  Client *Mythic_Engine::get_client() {
    return client;
  }

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
}