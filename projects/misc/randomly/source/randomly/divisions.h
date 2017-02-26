#pragma once

#include <vector>
#include <algorithm>
#include "Dice.h"

namespace randomly {
  namespace divisions {

    template<typename T>
    std::vector<T> create_simple(Dice &dice, int count, T range) {
      std::vector<T> result;
      result.reserve(count);

      for (int i = 0; i < count; ++i) {
        result[i] = get_generic<T>(dice, 0, range);
      }

      std::sort(result.begin(), result.end());
      return result;
    }
  }

}