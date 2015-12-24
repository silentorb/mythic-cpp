#include "Mythic_Engine.h"
#include "timing/Quartz.h"

namespace mythic {
  Mythic_Engine::Mythic_Engine(Client *client)
    : client(client) {
    timer = new timing::Quartz();
  }

  Mythic_Engine::~Mythic_Engine() {
    delete timer;
  }

  void Mythic_Engine::add_myth(Myth *myth) {
    myths[myth->get_name()] = unique_ptr<Myth>(myth);
  }

  Client *Mythic_Engine::get_client() {
    return client;
  }

  void Mythic_Engine::update() {
    float delta = timer->update();
    client->update();

    for(auto& myth: myths){
      myth.second->update(*this, delta);
    }
  }

  void Mythic_Engine::loop() {
    while (!client->is_closing()) {
      update();
    }
  }
}