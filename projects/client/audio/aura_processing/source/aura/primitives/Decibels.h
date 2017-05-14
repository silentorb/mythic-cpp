#pragma once

#include "Primitive.h"
#include "aura/processing/utility.h"

namespace aura {

  struct Decibels : public Primitive<float> {
      Decibels(float value) : Primitive(aura::to_db(value)) {}
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