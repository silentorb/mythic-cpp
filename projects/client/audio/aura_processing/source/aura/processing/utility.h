#pragma once
#include <cmath>

namespace aura {
  namespace processing {

    float to_dB(float value);
//    float to_dB(float value) {
////      return std::pow(value, 2);
////      const auto base = 10;
//      return (std::pow(10, value) - 1) / (10 - 1);
////      return 20 * log10(value);'
////      return std::pow(10.0f, value / 20.0f);
//    }
    float inverse_dB(float value);

    template<typename Signal_Type>
    Signal_Type clip(const Signal_Type &signal, Signal_Type limit = 1) {
      if (signal > limit)
        return limit;

      if (signal < -limit)
        return -limit;

      return signal;
    }

    template<typename Signal_Type>
    Signal_Type transition(float progress, const Signal_Type &start, const Signal_Type &end) {
      auto range = end - start;
      return range * progress + start;
    }

    template<typename Signal_Type>
    class Transition {
        const Signal_Type start;
        float range;

    public:
        Transition(const Signal_Type start, const Signal_Type end) : start(start) {
          range = end - start;
        }

        Signal_Type operator()(float progress) {
          return range * progress + start;
        }
    };

    template<typename Signal_Type>
    Signal_Type signal_range(const Signal_Type &signal, const Signal_Type &bottom, const Signal_Type &top) {
      return transition(signal * 0.5 + 0.5, bottom, top);
    }

  }
}