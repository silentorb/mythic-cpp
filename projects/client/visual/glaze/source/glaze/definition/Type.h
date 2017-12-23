#pragma once

#include <string>
using namespace std;

namespace glaze {
  namespace definition {

    class Type {
        string name;
        int size;

    public:
        Type(const string &name, int size) : name(name), size(size) { }

        const string &get_name() const {
          return name;
        }

        int get_size() const {
          return size;
        }
    };

//    struct Standard_Types {
//        Type vec3;
//        Type vec4;
//    };

//    extern Standard_Types types;
    namespace types {
      extern Type vec3;
      extern Type vec4;
      extern Type mat4;
    }
  }
}