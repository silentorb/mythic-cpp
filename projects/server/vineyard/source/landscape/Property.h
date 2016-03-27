#pragma once
#include "dllexport.h"
#include <string>

using namespace std;
class Trellis;

namespace landscape {

  class MYTHIC_EXPORT Property {
      const string name;
      Trellis & trellis;

  public:
      Property(const string &name, Trellis & trellis);
  };
}