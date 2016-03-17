#pragma once

#include "dllexport.h"
#include <random>
#include <vector>
#include <stdexcept>

namespace randomly {

  class MYTHIC_EXPORT Dice {
      std::mt19937 engine;

  public:
      Dice() { }

      Dice(unsigned int seed) {
        engine.seed(seed);
      }

      void seed(unsigned int seed) {
        engine.seed(seed);
      }

      float get_float() {
        return static_cast <float> (engine.operator()()) / static_cast <float> (engine.max());
      }

      float get_float(float min, float max) {
        return min + get_float() * (max - min);
      }

      int get_int(int min, int max) {
        return engine.operator()() % (max - min) + min;
      }

      int get_int(int max) {
        return engine.operator()() % max;
      }

      template<typename T>
      T get_item(std::vector<T> &items) {
        if (items.size() == 0)
          throw std::runtime_error("Cannot grab random item out of empty vector.");

        int index = get_int(items.size());
        return items[index];
      }
  };
}
