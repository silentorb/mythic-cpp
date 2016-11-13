#pragma once

#include <aura/processors/Timer.h>
#include <aura/utility/utility.h>
#include "Custom_Envelope.h"

namespace aura {

  class Envelope_Container {
      envelopes::Custom_Envelope_Instance instance;
      const envelopes::Custom_Envelope &envelope;
      Timer &timer;

  public:
      Envelope_Container(const envelopes::Custom_Envelope &envelope, Timer &timer) :
        instance(envelope, timer.get_duration()), envelope(envelope), timer(timer) {}

      float update() {
        auto value = envelope.update(instance, timer.get_progress(), timer.get_duration());
        return utility::to_db(value);
      }
  };
}