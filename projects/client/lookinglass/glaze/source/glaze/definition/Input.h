#pragma once

#include "dllexport.h"
#include <string>

using namespace std;

namespace glaze {
namespace definition {
  class MYTHIC_EXPORT Input {
  public:
      string name;
      int count;

      Input(const string &name, int count)
        : name(name), count(count) { }

      const string &get_name() const {
        return name;
      }

      int get_count() const {
        return count;
      }
  };
}
}