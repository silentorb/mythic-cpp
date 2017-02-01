#pragma once

#include <randomly/Dice.h>

namespace aura {
  namespace envelopes {

    class Random_Envelope {
        randomly::Dice &dice;
//        float rate = 1; // Per second
        double remaining_distance = 0;
        float modifier = 0;
        float current_value = 0;
        float min_gap = 0;
        float max_gap = 1;

    public:
        Random_Envelope(randomly::Dice &dice) :
          dice(dice) {

        }

        void set_min_gap(float value) {
          min_gap = value;
        }

        void set_max_gap(float value) {
          max_gap = value;
        }

        void set_gap_range(float min, float max) {
          min_gap = min;
          max_gap = max;
        }

        float operator()(float delta) {
          remaining_distance -= delta;
          if (remaining_distance < 0) {
            float next_value = dice.get_float();
            remaining_distance = dice.get_float(min_gap, max_gap);
            modifier = (float) ((next_value - current_value) / remaining_distance);
          }
          else {
            current_value += modifier * delta;
          }

          return current_value;
        }

    };
  }
}