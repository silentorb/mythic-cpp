#pragma once
#include "dllexport.h"

#include <string>

using namespace std;

namespace mythic {
  class MYTHIC_EXPORT Mythic_Engine;

  class MYTHIC_EXPORT Myth {
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