#pragma once

#include <string>

using namespace std;

namespace mythic {

  class Mythic_Engine;

  class Myth;

  class Myth_Info {
  public:
      virtual string get_name() = 0;
      virtual Myth *fabricate(Mythic_Engine &engine) = 0;
  };
}