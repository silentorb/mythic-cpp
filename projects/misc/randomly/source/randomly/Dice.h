#pragma once

#include "dllexport.h"
#include <random>
#include <vector>
#include <stdexcept>
#include <chrono>

namespace randomly {

  class MYTHIC_EXPORT Dice {
      std::mt19937 engine;

  public:
      Dice() {
        engine.seed(1);
      }

      Dice(unsigned int seed) {
        engine.seed(seed);
      }

      void seed(unsigned int seed) {
        engine.seed(seed);
      }

      void seed() {
        typedef std::chrono::high_resolution_clock dice_clock;
        dice_clock::time_point beginning = dice_clock::now();
        dice_clock::duration d = dice_clock::now() - beginning;
        engine.seed(d.count());
      }

      float get_float() {
        return static_cast <float> (engine.operator()()) / static_cast <float> (engine.max());
      }

      float get_float(float min, float max) {
        return min + get_float() * (max - min);
      }

      float get_float_relative(float a, float b) {
        return b > a
               ? a + get_float() * (b - a)
               : b + get_float() * (a - b);
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
