#pragma once
#include <string>

using namespace std;

namespace lookinglass {
  namespace modeling {
    struct Vertex_Attribute {
        string name;
        int count;
//        int type;
//        int stride;

        Vertex_Attribute(const string &name, int count)
          : name(name), count(count) {

        }
    };
  }
}