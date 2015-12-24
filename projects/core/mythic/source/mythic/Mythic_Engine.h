#pragma once

#include "clienting/Client.h"
#include "Myth.h"
#include <map>
#include <memory>

using namespace clienting;
using namespace std;

namespace timing {
  class Quartz;
}

namespace mythic {
  class Mythic_Engine {
  private:
      timing::Quartz *timer;
      Client *client;
      std::map<string, unique_ptr<Myth>> myths;

  public:
      Mythic_Engine(Client *client);
      ~Mythic_Engine();

      void add_myth(Myth *myth);
      Client *get_client();
      void update();
      void loop();
  };
}