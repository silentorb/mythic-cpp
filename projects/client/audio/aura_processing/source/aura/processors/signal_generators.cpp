#include "signal_generators.h"
#include "randomly/Dice.h"

randomly::Dice dice;

static std::vector<float> sine_buffer;

namespace aura {

  namespace generate {
      
      void initialize() {
          long range = 44100;
          sine_buffer.resize(range);
          for(long i = 0; i < range; ++i) {
              float position = (float)i / (float)range;
              sine_buffer[i] = (float) sin(position * 2 * Pi);
          }
      }

    namespace ranged {

      float triangle(float x) {
        float a = x * 4;
        if (x < 0.25)
          return a;

        if (x < 0.75)
          return 2 - a;

        return a - 4;
      }

    }

    float smooth;

    float white_noise() {
      auto sample = dice.get_float(-1, 1);
      float amount = 0.5;
      smooth = smooth - (amount * (smooth - sample));
      return smooth;
    }

    float white_noise(randomly::Dice &dice) {
      auto sample = dice.get_float(-1, 1);
      float amount = 0.5;
      smooth = smooth - (amount * (smooth - sample));
      return smooth;
    }

    float sine(float position) {
//      return (float) sin(position * 2 * Pi);
        int index = position * sine_buffer.size();
        return sine_buffer[index];
    }

    float saw(float position) {
//      return (float) fabs(fmod(position, 2) - 1);
      return (float) position - 1;
    }

//    float triangle(float position) {
//      auto value = fmod(position, 2);
//      return position > 0
//    }

    float square(float position) {
//      return fmod(position, 1) < 0.5 ? 1 : -1;
      return position < 0.5 ? 1 : -1;
    }

    // For performance and simplicity this does not have the same phase as square(float)
    float square_pulse_width(float position, float pulse_width) {
      float half = (1 - pulse_width) * 0.5f;
      float value = (float)fmod(position, 1);
      return value > half && value < 1 - half
             ? 1
             : -1;
    }

    float triangle(double position) {
      float x = fmod(position, 1);
      return ranged::triangle(x);
    }
  }
}

