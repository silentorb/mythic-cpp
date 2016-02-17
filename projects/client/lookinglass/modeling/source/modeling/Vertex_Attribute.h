#pragma once

#include "dllexport.h"
#include <string>

using namespace std;

namespace modeling {
  class Vertex_Attribute {
  public:
      string name;
      int count;

      Vertex_Attribute(const string &name, int count)
        : name(name), count(count) { }

      const string &get_name() const {
        return name;
      }

      int get_count() const {
        return count;
      }
  };
}
