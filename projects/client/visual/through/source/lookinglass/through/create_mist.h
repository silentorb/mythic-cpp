#pragma once

#include "glow.h"
#include "glow/Capabilities.h"
#include "Mist.h"
#include "Buffer_Mist.h"
#include "Ancient_Mist.h"

using namespace shading;
using namespace glow;

namespace lookinglass {

  namespace through {

    template<typename T>
    MYTHIC_EXPORT Mist<T> *create_mist(Struct_Info *info) {

      auto &version = Capabilities::get_version();
      Mist<T> *result = version.major < 3
                        ? (Mist<T> *) new Ancient_Mist<T>()
                        : (Mist<T> *) new Buffer_Mist<T>();
//      auto result = new Buffer_Mist<T>();
      result->initialize(info);
      return result;
    }
  }
}