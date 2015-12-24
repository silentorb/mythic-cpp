#pragma once

#include <string>

using namespace std;

namespace mythic {
  class Mythic_Engine;

  class Myth {
  protected:
      Mythic_Engine &engine;
      Myth(Mythic_Engine &engine);

  public:
      string get_name();
      virtual void update(float delta);

      Mythic_Engine &getEngine() const {
        return engine;
      }
  };
}