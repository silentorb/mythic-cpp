#pragma once

#include "Myth.h"
#include <map>
#include <memory>

namespace timing {
  class Quartz;
}

namespace clienting {
  class Client;
}

namespace lookinglass {
  class Renderable;
}

using namespace clienting;
using namespace std;

namespace mythic {

  class Mythic_Renderer;

  class Mythic_Engine {
  private:
      timing::Quartz *timer;
      Client *client;
      std::map<string, unique_ptr<Myth>> myths;
      Mythic_Renderer *renderer;

  public:
      Mythic_Engine(Client *client);
      ~Mythic_Engine();

      void add_myth(Myth *myth);
      void add_renderable(lookinglass::Renderable*renderable);
      Client *get_client();
      void update();
      void loop();
  };
}