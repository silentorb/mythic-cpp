#pragma once

#include "dllexport.h"
#include "Input.h"
#include <vector>

using namespace std;

namespace glaze {
namespace definition {
  class MYTHIC_EXPORT Material {
      vector<Input> inputs;

  public:

      Material() { }

      Material(initializer_list<Material *> mixins) { }
  };
}
}