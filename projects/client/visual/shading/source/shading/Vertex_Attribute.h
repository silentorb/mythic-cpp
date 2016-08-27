#pragma once

#include "commoner/dllexport.h"
#include <string>

using namespace std;

namespace shading {

  class Vertex_Attribute {
  public:
      int id;
      string name;
      int count;

      Vertex_Attribute(int id, const string &name, int count)
        : id(id), name(name), count(count) { }

      const string &get_name() const {
        return name;
      }

      int get_count() const {
        return count;
      }

      int get_id() const {
        return id;
      }
  };
}
