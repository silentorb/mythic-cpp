#pragma once

#include "Primitive.h"
#include "utility.h"

namespace aura {
  namespace processing {

        struct Decibels : public Primitive<float> {
            Decibels(float value) : Primitive(to_dB(value)) {}
//            static Decibels convert(float value) {
//              Decibels result;
//              result.value = to_dB(value);
//              return result;
//            }

            operator float() const {
              return get_value();
            }
        };
  }
}