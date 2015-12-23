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

  Client *Mythic_Engine::get_client() {
    return client;
  }

  void Mythic_Engine::update() {
    float delta = timer->update();
    client->update();
  }

  void Mythic_Engine::loop() {
    while (!client->is_closing()) {
      update();
    }
  }
}