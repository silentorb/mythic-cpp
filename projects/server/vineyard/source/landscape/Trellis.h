#pragma once

#include "dllexport.h"
#include "Property.h"
#include <string>
#include <vector>

using namespace std;

namespace landscape {

  class MYTHIC_EXPORT Trellis {
      const string name;
      vector<Property> properties;
  };
}