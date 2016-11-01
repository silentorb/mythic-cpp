#pragma once

#include <vector>
#include "External.h"

namespace signal_graph {

  class Externals {
      std::vector<const void *> external_values;

  public:
      Externals(std::initializer_list<const void *> initializer) :
        external_values(initializer) {}

      template<typename T>
      const T &get_external(const External &external) const {
        return *(T *) external_values[external.get_index()];
      }
  };
}
