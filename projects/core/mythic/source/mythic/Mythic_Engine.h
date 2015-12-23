#pragma once

#include "clienting/Client.h"

using namespace clienting;

namespace timing {
  class Quartz;
}

namespace mythic {
  class Mythic_Engine {
  private:
      timing::Quartz *timer;
      Client *client;

  public:
      Mythic_Engine(Client*client);
      ~Mythic_Engine();

      Client *get_client();
      void update();
      void loop();
  };
}