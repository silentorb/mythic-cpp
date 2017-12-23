#pragma once

#include "glow.h"
#include "glow/Capabilities.h"
#include "Mist.h"
#include "Buffer_Mist.h"
#include "Ancient_Mist.h"

using namespace shading;
using namespace glow;

namespace through {

  template<typename T>
  Mist<T> *create_mist(Struct_Info *info) {

    Mist<T> *result = !Capabilities::get_instance().uniform_buffer()
                      ? (Mist<T> *) new Ancient_Mist<T>()
                      : (Mist<T> *) new Buffer_Mist<T>();
//      auto result = new Buffer_Mist<T>();
    result->initialize(info);
    return result;
  }
}
