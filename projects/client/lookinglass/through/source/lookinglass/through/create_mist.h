#pragma once

#include "lookinglass/glow.h"
#include "lookinglass/glow/Capabilities.h"
#include "Mist.h"
#include "Buffer_Mist.h"
#include "Ancient_Mist.h"

namespace lookinglass {
  using namespace glow;
  using namespace shading;

  namespace through {

    template<typename T>
    MYTHIC_EXPORT Mist<T> *create_mist(Struct_Info *info, const Capabilities &capabilities) {

      auto &version = capabilities.get_version();
      Mist<T> *result = version.major < 3
                        ? (Mist<T> *) new Ancient_Mist<T>()
                        : (Mist<T> *) new Buffer_Mist<T>();
//      auto result = new Buffer_Mist<T>();
      result->initialize(info);
      return result;
    }
  }
}