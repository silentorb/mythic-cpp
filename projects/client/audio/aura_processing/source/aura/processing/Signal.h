#pragma once

#include "Primitive.h"

namespace aura {
  namespace processing {

    template<typename Type>
    struct Signal : public Primitive<Type> {
        Signal(Type value) : Primitive<Type>(value) {}
    };
  }
};