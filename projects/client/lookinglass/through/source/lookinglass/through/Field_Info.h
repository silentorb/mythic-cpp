#pragma once

#include <string>
#include "Field_Type.h"

using namespace std;

namespace lookinglass {
  namespace through {

    struct Field_Info {
    private:

    public:
        string name;
        Field_Type type;
        int length;

        Field_Info(const string &name, const Field_Type &type) : name(name), type(type) {
          length = Field_Type_Lengths[type];
        }
    };
  }
}


