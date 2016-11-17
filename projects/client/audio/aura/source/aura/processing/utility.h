#pragma once

namespace aura {
  namespace processing {

    float dB(float value);
    float inverse_dB(float value);

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
  }
}