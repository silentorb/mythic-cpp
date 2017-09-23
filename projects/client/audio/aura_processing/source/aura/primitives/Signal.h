#pragma once

#include "Primitive.h"

namespace aura {
  template<typename Type>
  struct Signal : public Primitive<Type> {
      Signal(Type value) : Primitive<Type>(value) {}
  };
};