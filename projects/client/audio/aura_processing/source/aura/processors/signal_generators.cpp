#include "signal_generators.h"
#include "randomly/Dice.h"

randomly::Dice dice;

static std::vector<float> sine_buffer;
const static unsigned long sine_buffer_range = 44100;
namespace aura {

  namespace generate {

    void initialize() {
      sine_buffer.resize(sine_buffer_range + 1);
      for (long i = 0; i < sine_buffer_range; ++i) {
        float position = (float) i / (float) sine_buffer_range;
        sine_buffer[i] = (float) sin(position * 2 * Pi);
      }

      // Add a single sample for solid 1
      // Loops don't return 1 but rounding from long double to float can cause it to become 1
      sine_buffer[sine_buffer_range] = (float) sin(2 * Pi);
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
      unsigned int index = (unsigned int)(position * sine_buffer_range);

      auto result = sine_buffer[index];
      auto k = (float) sin(position * 2 * Pi);
      auto diff = fabs(result - k);
      if (diff > 0.001) {
        int j = 0;
      }
      return sine_buffer[index];
    }

    float cosine(float position) {
      auto p = position + 0.25f;
      if (p > 1)
        p -= 1;

      return sine(p);
//      auto p2 = Pi * Pi;
//      auto result = sine(position + Pi / 2);
//      auto i = sin(position * 2 * Pi + Pi / 2);
//      auto k = cos(position * 2 * Pi);
//      return result;
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
      float value = (float) fmod(position, 1);
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

