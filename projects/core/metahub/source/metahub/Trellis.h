#pragma once

#include "Entity.h"
#include <string>
#include <vector>

using namespace std;

namespace metahub {

  struct Trellis : public Entity {
      string *name;
      vector<Guid> *properties;
  };

  Guid& trellis_create_property();
}