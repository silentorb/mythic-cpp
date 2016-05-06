#pragma once
#include "dllexport.h"

#include <string>

using namespace std;

namespace mythic {
  class MYTHIC_EXPORT Mythic_Engine;

  class MYTHIC_EXPORT Myth : no_copy {
  protected:
      Mythic_Engine &engine;
      Myth(Mythic_Engine &engine);

  public:
      virtual ~Myth() {}
      virtual string get_name() = 0;
      virtual void update(float delta);

      Mythic_Engine &getEngine() const {
        return engine;
      }
  };
}