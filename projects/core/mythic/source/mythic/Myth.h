#pragma once
#include <string>

namespace mythic {
  class Mythic_Engine;

  class Myth {
  public:
      virtual std::string get_name()= 0;
      virtual void start(Mythic_Engine &engine);
      virtual void stop(Mythic_Engine &engine);
      virtual void update(Mythic_Engine &engine, float delta);
  };
}