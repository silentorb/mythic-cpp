#pragma once

#include <aura/processing/Timer.h>
#include <aura/processing/utility.h>
#include "Custom_Envelope.h"
#include "Absolute_Envelope.h"

namespace aura {
  namespace envelopes {

    class Envelope_Container {
        envelopes::Custom_Envelope_Instance instance;
        Absolute_Envelope envelope;
//        const envelopes::Custom_Envelope &envelope;
        processing::Time_Source &timer;
        float value;

    public:
        Envelope_Container(const envelopes::Custom_Envelope &envelope, processing::Time_Source &timer) :
          instance(envelope, timer.get_duration()), envelope(envelope, timer.get_duration()), timer(timer) {}

        float update() {
          value = envelope.update(instance, timer.get_position(), timer.get_duration());
          value = to_db(value);
          return value;
        }

        float operator()() {
          return update();
        }

        float get_value() const {
          return value;
        }
    };
  }
}