#pragma once

#include <aura/processing/Timer.h>
#include <aura/processing/utility.h>
#include "Custom_Envelope.h"

namespace aura {

  class Envelope_Container {
      envelopes::Custom_Envelope_Instance instance;
      const envelopes::Custom_Envelope &envelope;
      processing::Timer &timer;

  public:
      Envelope_Container(const envelopes::Custom_Envelope &envelope, processing::Timer &timer) :
        instance(envelope, timer.get_duration()), envelope(envelope), timer(timer) {}

      float update() {
        auto value = envelope.update(instance, timer.get_position(), timer.get_duration());
        return processing::to_dB(value);
      }

      float operator()() {
        return update();
      }
  };
}