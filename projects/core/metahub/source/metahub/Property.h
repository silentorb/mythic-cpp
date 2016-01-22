#pragma once

#include <string>
#include "Trellis.h"

using namespace std;

namespace metahub {

  enum Property_Type  {
      String,
      Int,
      Bool,
      Float,
      Reference_Array
  };

  struct Property : public Entity {
      string *name;
      Property_Type type;
      int offset;
  };
};