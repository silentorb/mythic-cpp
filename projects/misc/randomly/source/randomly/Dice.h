#pragma once

#include "commoner/dllexport.h"
#include <commoner/assert.h>
#include <random>
#include <vector>
#include <stdexcept>
#include <chrono>

namespace randomly {

  class MYTHIC_EXPORT Dice {
      std::mt19937 engine;
      unsigned int _seed;

  public:
      Dice() {
        seed();
      }

      Dice(unsigned int seed) {
        _seed = seed;
        engine.seed(seed);
      }

      void seed(unsigned int seed) {
        _seed = seed;
        engine.seed(seed);
      }

      void seed() {
        _seed = (unsigned int) time(NULL);
        engine.seed(_seed);
      }

      float get_float() {
        return static_cast <float> (engine.operator()()) / static_cast <float> (engine.max());
      }

      float get_float(float max) {
        return get_float() * max;
      }

      float get_float(float min, float max) {
        return min + get_float() * (max - min);
      }

      double get_double() {
        return static_cast <double> (engine.operator()()) / static_cast <double> (engine.max());
      }

      double get_double(double max) {
        return get_double() * max;
      }

      float get_centered_float(float range) {
        return get_float(-range, range);
      }

      float get_float_relative(float a, float b) {
        return b > a
               ? a + get_float() * (b - a)
               : b + get_float() * (a - b);
      }

      int get_int(int min, int max) {
        if (min == max)
          return min;

        auto value = engine.operator()();
        return value % (max - min) + min;
      }

      int get_int(int max) {
        Assert(max > 0);
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
