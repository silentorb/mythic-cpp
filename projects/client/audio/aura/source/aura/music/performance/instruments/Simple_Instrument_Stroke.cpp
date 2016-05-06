#include "Simple_Instrument_Stroke.h"

namespace aura {

  float Simple_Instrument_Stroke::update(float beat_delta) {
    progress += beat_delta;
    auto value = oscillator->update();
    return value * volume_envelope->get_value(progress);
  }


}