#pragma once


#include "Type.h"
#include <string>

using namespace std;

namespace glaze {
  namespace definition {

    class Variable {
        string name;
        const Type& type;
        int count;

    public:


        Variable(const Type &type, const string &name, int count = 1) : type(type), name(name), count(count) { }

        const string &get_name() const {
          return name;
        }

        int get_count() const {
          return count;
        }

        const Type &get_type() const {
          return type;
        }
    };
  }
}