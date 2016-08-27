#pragma once

#include <string>
#include <memory>
#include "Field_Type.h"

using namespace std;

namespace lookinglass {
  namespace through {

    class Field_Info {
    private:

    public:
        string name;
        Field_Type type;
        int length;
//        unique_ptr<Field_Info> subtype;

        Field_Info(const string &name, const Field_Type &type) : name(name), type(type) {
          length = Field_Type_Lengths[type];
        }

//        Field_Info(const string &name, const Field_Type &type, Field_Info *subtype) :
//          name(name), type(type), subtype(subtype) {
//          length = Field_Type_Lengths[type];
//        }
    };
  }
}


