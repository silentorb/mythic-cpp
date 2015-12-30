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
    MYTHIC_EXPORT Mist<T> *create_mist(unsigned int id, const char* name, const std::map<string, Program *> &programs,
                                       const Capabilities &capabilities) {

      Data_Buffer buffer;
      buffer.update(nullptr);
      auto result = capabilities.get_version().major < 3
                    ? (Mist<T> *) new Ancient_Mist<T>()
                    : (Mist<T> *) new Buffer_Mist<T>();
//      auto result = new Buffer_Mist<T>();
      result->initialize(id, name, programs);
      return result;
    }
  }
}